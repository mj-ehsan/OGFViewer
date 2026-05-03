# OGF Viewer 1.0.2

## Description

**OGF Viewer 1.0.2** is legacy model viewer for OGF format from S.T.A.L.K.E.R. Shadow of Chernobyl.  
I've uploaded this project to GitHub because the status and hosting reliability of the original source, [stalkerin.gameru.net][stgameru_link], became uncertain.


> [!CAUTION]
> Please note that the source code for **Version 1.0.3** and **Version 1.0.4** were not found; it is possible these versions were never publicly released.  
> Furthermore, any version labeled 1.0.5 found elsewhere online is not affiliated with, nor part of, this software

> [!IMPORTANT]
> If you want to research original source code just switch branch into [legacy][legacy_link]

> [!NOTE]
> The most significant update in this version is that it has been successfully recompiled and built using modern Microsoft compilers. For a detailed breakdown of changes, please refer to the changelog below.

## Requirements

* Visual Studio 2017 (and above)
* Microsoft Visual C++ v141
* MFC for MSVC v141

## Dependencies

* GLext (located in repo; see [source][glext_link])
* GLew 2.3.1 (located in repo; see [source][glew_link])

## Credits

### Information

**Author:** batya  
**Last date:** 18.11.2006  
**Source link:** [link][ogfv_dload_link]  

### Changelog

**Version 1.0.2a**
* Converted solution and project to actual Visual Studio format (VS2017 supported)
* Changed stdafx.h: just update some macros
* Replaced GLee library to GLew 2.3.1 cause of compatible
* Located GLext library in repository

**Version 1.0.2**  
* Added mouse rotation (LMB)
* Added mouse scaling (RMB)
* Added fixed bug with module loading (memory leaks) 

**Version 1.0.1**
* Initial release

## License

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[ogfv_dload_link]: http://stalkerin.gameru.net/modules.php?name=Downloads&d_op=viewdownload&cid=10&min=10&orderby=titleA&show=10
[stgameru_link]: http://stalkerin.gameru.net
[legacy_link]: https://github.com/justtails/OGFViewer/tree/legacy
[glew_link]: https://sourceforge.net/projects/glew/
[glext_link]: https://sourceforge.net/projects/glextwin32/
