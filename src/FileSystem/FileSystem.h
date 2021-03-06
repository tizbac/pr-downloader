/* This file is part of pr-downloader (GPL v2 or later), see the LICENSE file */

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <list>
#include <string>

class SRepository;
class CRepo;
class FileData;
class IDownload;

#ifdef WIN32
struct _FILETIME;
#endif

#define IO_BUF_SIZE 4096


class CFileSystem
{
	static CFileSystem* singleton;

public:
	static CFileSystem* GetInstance();
	static void Shutdown();

	CFileSystem();
	~CFileSystem();
	/**
		parses the file for a mod and creates
	*/
	bool parseSdp(const std::string& filename, std::list<FileData*>& files);
	/**
	 *	Validates a pool-file, (checks the md5)
	 */
	bool fileIsValid(const FileData* mod, const std::string& filename) const;

	/**
		returns the spring writeable directory
	*/
	const std::string& getSpringDir();

	/**
		checks if a directory exists
	*/
	bool directoryExists(const std::string& path) const;

	/**
		creates directory if it doesn't exist, expects PATH_DELIMETER at the end of the path
		creates a directory with all subdirectorys (doesn't handle c:\ ...)
	*/
	bool createSubdirs(const std::string& path) const;

	/**
		Validate all files in /pool/ (check md5)
		@return count of valid files found
	*/
	int validatePool(const std::string& path);

	/**
		check if file is older then secs, returns true if file is older or something goes wrong
	*/
	bool isOlder(const std::string& filename, int secs);
	/**
		check if a file is readable
	*/
	bool fileExists(const std::string& filename);
	/**
	*
	*	parses the bencoded torrent data, strucutre is like this:
	*	dict {
	*		info => dict {
	*			length => int = 21713638
	*			name => str = ba750.sdz (len = 9)
	*			piece length => int = 262144
	*			pieces => str = <sha1 checksums>
	*		}
	*	}
	*
	*/
	bool parseTorrent(const char* data, int size, IDownload* dl);
	/**
	*	dumps info about the given .sdp
	*/
	bool dumpSDP(const std::string& filename);
	/**
	*	extracts a 7z file to dstdir
	*/
	bool extract(const std::string& filename, const std::string& dstdir);

	bool setWritePath(const std::string& path);

	/**
	*	returns full filename for pool file from md5
	*/
	void getPoolFilename(const std::string& md5str, std::string& path);

	/**
	*	tries to rename a file, copies if rename fails
	*/
	bool Rename(const std::string& source, const std::string& destination);


	std::string EscapePath(const std::string& path);

#ifdef WIN32
	long FiletimeToTimestamp(const _FILETIME& time);
	void TimestampToFiletime(const time_t t, _FILETIME& pft);
#endif

private:
	std::list<std::string> tmpfiles;
	std::list<FileData> mods;
	bool parse_repository_line(char* str, SRepository* repository, int size);
	std::string springdir;
};

#define fileSystem CFileSystem::GetInstance()

#ifdef WIN32
#define PATH_DELIMITER '\\'
#else
#define PATH_DELIMITER '/'
#endif

#endif
