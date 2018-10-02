#include <iostream>
#include <apt-pkg/cachefile.h>
#include <apt-pkg/pkgcache.h>
// g++ -w -o testapt testapt.cxx -I/usr/include/apt-pkg -lapt-pkg
int main()
{
// _config and _system are defined in the libapt header files
	pkgInitConfig(*_config);
	pkgInitSystem(*_config, _system);
	pkgCacheFile cache_file;     
	pkgCache* cache = cache_file.GetPkgCache();
	for (pkgCache::PkgIterator package = cache->PkgBegin(); !package.end(); package++)
	{
		std::cout << package.Name() << std::endl;
	}
	return 0; 
}
