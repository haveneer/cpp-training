//#region [Collapse all]
#include <zlib.h>
#define CHUNK 256
int main() {
  z_stream strm;
  /* allocate deflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  int level = 0;
  int ret = deflateInit(&strm, level);
  if (ret != Z_OK)
    return ret;
}
//#endregion