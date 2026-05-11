#include "pch.h"

#include "OGFLoader.h"

#include <nv_dds.h>

using namespace nv_dds;

void ReadChunk1284(ifstream& stream, i32 pos, OGFModel& model, const std::string& pathToTextures)
{
	stream.seekg(pos, ios_base::beg);

	Chunk1284 c1284;
	stream.read(reinterpret_cast<char*>(&c1284), sizeof(Chunk1284));

	if (c1284.header[0] != 1 && c1284.header[1] != 44 && (c1284.header[2] != 1284 || c1284.header[2] != 1028))
	{
		return;
	}

	TextData td = {};
	stream.read(reinterpret_cast<char*>(&td.type), sizeof(i32));
	stream.read(reinterpret_cast<char*>(&td.size), sizeof(i32));
	stream.read(td.data, td.size);

	model.m_MaterialCount++;
	char* materialName = strcat(td.data, ".dds");

	std::string fullName(pathToTextures);
	fullName += std::string(materialName);

	CDDSImage image;
	GLuint texobj;

	if (image.load(fullName.c_str()))
	{
		glGenTextures(1, &texobj);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texobj);

		glCompressedTexImage2DARB(GL_TEXTURE_2D, 0, image.get_format(), 
								  image.get_width(), image.get_height(), 0, 
								  image.get_size(), image);

		for (i32 i = 0; i < image.get_num_mipmaps(); i++)
		{
			glCompressedTexImage2DARB(GL_TEXTURE_2D, i + 1, image.get_format(), 
									  image.get_mipmap(i).get_width(), image.get_mipmap(i).get_height(), 0,
									  image.get_mipmap(i).get_size(), image.get_mipmap(i));
		}
		model.m_Material[model.m_MaterialCount - 1].m_MaterialID = texobj;
	}
	else
	{
		model.m_Material[model.m_MaterialCount - 1].m_MaterialID = 0;
	}

	i32 num, size, ident, numverts;
	stream.read(reinterpret_cast<char*>(&num), sizeof(i32));
	stream.read(reinterpret_cast<char*>(&size), sizeof(i32));
	stream.read(reinterpret_cast<char*>(&ident), sizeof(i32));
	
	//	ident = 302455168;		Проверял на 2х файлах
	stream.read(reinterpret_cast<char*>(&numverts), sizeof(i32));
	if (ident == 302455168)
	{
		std::vector<OGFVertex> v(numverts);
		stream.read(reinterpret_cast<char*>(v.data()), numverts * sizeof(OGFVertex));

		model.m_Material[model.m_MaterialCount - 1].m_VerticesCount = numverts;
		model.m_Material[model.m_MaterialCount - 1].m_Vertices = std::vector<Vertex>(numverts);
		OGFVertex vert;
		Vertex mVertex;
		for (i32 i = 0; i < numverts; i++)
		{
			vert = v[i];
			mVertex.x = vert.x / 1.5f;
			mVertex.y = vert.y;
			mVertex.z = vert.z;
			mVertex.tx = vert.s[1];
			mVertex.ty = -vert.d[0];
			model.m_Material[model.m_MaterialCount - 1].m_Vertices[i] = mVertex;
		}

		i32 type, datasize, count;
		stream.read(reinterpret_cast<char*>(&type), sizeof(i32));
		stream.read(reinterpret_cast<char*>(&datasize), sizeof(i32));
		stream.read(reinterpret_cast<char*>(&count), sizeof(i32));

		Indices indices;
		indices.count = count;
		indices.idx = new u16[count];

		stream.read(reinterpret_cast<char*>(indices.idx), count * sizeof(u16));
		model.m_Material[model.m_MaterialCount - 1].m_Indices = new u32[count];
		model.m_Material[model.m_MaterialCount - 1].m_IndicesCount = count;

		for (i32 i = 0; i < count; i++)
		{
			model.m_Material[model.m_MaterialCount - 1].m_Indices[i] = indices.idx[i];
		}
		delete indices.idx;
	}
}

std::unique_ptr<OGFModel> Load(char* fileName, const std::string& pathToTextures)
{
	std::ifstream stream(fileName, ios_base::binary);

	glewInit(); // GLeeInit();

	if (!stream.is_open())
	{
		return nullptr;
	}

	auto model = std::make_unique<OGFModel>();

	stream.seekg(0, std::ios::beg);

	/* OgfChunk chunk;
	fread_s(&chunk, sizeof(chunk), sizeof(OgfChunk), 1, inputFile);

	if (chunk.ChunkType == static_cast<u32>(OgfChunkTypes::OGF_HEADER))
	{
			TODO(Проверка на компрессию - ChunkType & ~0x80000000);
	} */

	Chunk2564 c2564;
	stream.read(reinterpret_cast<char*>(&c2564), sizeof(Chunk2564));

	OGFHeader header = {};

	stream.read(reinterpret_cast<char*>(&header.count), sizeof(i32));
	stream.read(reinterpret_cast<char*>(&header.size), sizeof(i32));

	stream.read(header.modelname, header.size);
	header.modelname[header.size] = '\0';

	stream.read(reinterpret_cast<char*>(&header.hz1), sizeof(i32));
	header.pos1 = stream.tellg();
	stream.read(reinterpret_cast<char*>(&header.hz2), sizeof(i32));
	header.pos2 = stream.tellg();
	stream.read(reinterpret_cast<char*>(&header.hz3), sizeof(i32));
	header.pos3 = stream.tellg();
	stream.read(reinterpret_cast<char*>(&header.hz4), sizeof(i32));
	header.pos4 = stream.tellg();

	ReadChunk1284(stream, header.pos1 + header.hz1 + 3, *model, pathToTextures);

	stream.seekg(header.pos2 + header.hz2, std::ios_base::beg);

	structF ds = {};
	stream.read(reinterpret_cast<char*>(&ds), sizeof(structF));

	Bone bone;
	stream.read(reinterpret_cast<char*>(&bone.id), sizeof(i32));
	stream.read(reinterpret_cast<char*>(&bone.bone), ds.f[1] - sizeof(i32));

	stream.read(reinterpret_cast<char*>(&ds), sizeof(structF));

	if (header.hz2 != header.hz4 + 8)
	{
		ReadChunk1284(stream, header.pos4 + header.hz4 + 8, *model, pathToTextures);
	}
	// Log::Get().Write("<!> OGF : Loaded %s successfull", fileName);
	// inputFile.Close();
	return model;
}