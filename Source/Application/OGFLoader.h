#pragma once

#include "OGFModel.h"

/**
 * @brief Типы блоков OGF
 * @authors bardak, abramcumner
 * @copyright Do whatever you want, just do not say you wrote it.
 */
enum class OgfChunkTypes : u32
{
	OGF_HEADER = 0x1,

	// build 729
	OGF2_TEXTURE = 0x2,
	OGF2_TEXTURE_L = 0x3,
	OGF2_BBOX = 0x6,
	OGF2_VERTICES = 0x7,
	OGF2_INDICES = 0x8,
	OGF2_VCONTAINER = 0xb,
	OGF2_BSPHERE = 0xc,

	OGF3_TEXTURE = 0x2,
	OGF3_TEXTURE_L = 0x3,
	OGF3_CHILD_REFS = 0x5,
	OGF3_BBOX = 0x6,
	OGF3_VERTICES = 0x7,
	OGF3_INDICES = 0x8,
	OGF3_LODDATA = 0x9, // not sure
	OGF3_VCONTAINER = 0xa,
	OGF3_BSPHERE = 0xb,
	OGF3_CHILDREN_L = 0xc,
	OGF3_S_BONE_NAMES = 0xd,
	OGF3_S_MOTIONS = 0xe, // build 1469 - 1580
	OGF3_DPATCH = 0xf,	  // guessed name
	OGF3_LODS = 0x10,	  // guessed name
	OGF3_CHILDREN = 0x11,
	OGF3_S_SMPARAMS = 0x12,		// build 1469
	OGF3_ICONTAINER = 0x13,		// build 1865
	OGF3_S_SMPARAMS_NEW = 0x14, // build 1472 - 1865
	OGF3_LODDEF2 = 0x15,		// build 1865
	OGF3_TREEDEF2 = 0x16,		// build 1865
	OGF3_S_IKDATA_0 = 0x17,		// build 1475 - 1580
	OGF3_S_USERDATA = 0x18,		// build 1537 - 1865
	OGF3_S_IKDATA = 0x19,		// build 1616 - 1829, 1844
	OGF3_S_MOTIONS_NEW = 0x1a,	// build 1616 - 1865
	OGF3_S_DESC = 0x1b,			// build 1844
	OGF3_S_IKDATA_2 = 0x1C,		// build 1842 - 1865
	OGF3_S_MOTION_REFS = 0x1D,	// build 1842

	OGF4_TEXTURE = 0x2,
	OGF4_VERTICES = 0x3,
	OGF4_INDICES = 0x4,
	OGF4_P_MAP = 0x5,
	OGF4_SWIDATA = 0x6,
	OGF4_VCONTAINER = 0x7,
	OGF4_ICONTAINER = 0x8,
	OGF4_CHILDREN = 0x9,
	OGF4_CHILDREN_L = 0xa,
	OGF4_LODDEF2 = 0xb,
	OGF4_TREEDEF2 = 0xc,
	OGF4_S_BONE_NAMES = 0xd,
	OGF4_S_MOTIONS = 0xe,
	OGF4_S_SMPARAMS = 0xf,
	OGF4_S_IKDATA = 0x10,
	OGF4_S_USERDATA = 0x11,
	OGF4_S_DESC = 0x12,
	OGF4_S_MOTION_REFS_0 = 0x13, // pre-CS format
	OGF4_SWICONTAINER = 0x14,
	OGF4_GCONTAINER = 0x15,
	OGF4_FASTPATH = 0x16,
	OGF4_S_LODS = 0x17,
	OGF4_S_MOTION_REFS_1 = 0x18, // introduced in clear sky
};

/**
 * @brief Версии OGF
 * @authors bardak, abramcumner
 * @copyright Do whatever you want, just do not say you wrote it.
 */
enum class OgfVersion : u8
{
	OGF2_VERSION = 2,
	OGF3_VERSION = 3,
	OGF4_VERSION = 4
};

struct OgfChunk
{
	u32 ChunkType;
	u32 Size;
};

struct OgfHeader_v3
{
	u8 Version;
	u8 ModelType;
	u16 _unused;
};

struct OgfHeader_v4
{
	u8 Version;
	u8 ModelType;
	u16 ShaderId;
	BBox Box;
	BSphere Sphere;
};

struct Chunk2564
{
	i32 header[3];	// 1 44 2564
	float info[10]; // data chunk
};

struct Chunk1284
{
	i32 header[3]; // 1 44 284
	char data[40];
};

struct OGFHeader
{
	i32 count;
	i32 size;
	char modelname[1024];
	i32 hz1; // 9
	i32 pos1;
	i32 hz2; // 1638
	i32 pos2;
	i32 hz3; // 0
	i32 pos3;
	i32 hz4; // 1630
	i32 pos4;
};

struct Bone
{
	i32 id;
	char bone[8192];
};

struct structF
{
	i32 f[2];
};

struct TextData
{
	i32 type;
	i32 size;
	char data[1024];
};

struct Indices
{
	i32 count;
	u16* idx;
};

struct OGFVertex
{
	float x, y, z;
	float t1, t2;
	float aa;
	char flag;
	float t[2];
	float b[2];
	float s[2];
	float d[2];
};

std::unique_ptr<OGFModel> Load(char* fileName, const std::string& pathToTextures);