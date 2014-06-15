#include "piCam.h"


struct serial_t tagFile(FILE* file, std::string tag, struct timeval time);
void serial_t camLong(){
	
	vidCall << 
	FILE* video;
	struct timeval time;
	if (gettimeofday(&time, NULL)) throw 4;
	system("raspivid -n -f 50 -t 30000 -o long_video.h264"); //thirty second clip
	return;
	//video = fopen("long_video.h264", "r");
	//if (video = NULL) throw 1;
	//return tagFile(video, "LVid", time);
}

void serial_t camShort(){
	static int count = 0;
	std::stringstream vidCall;
	vidCall << "raspivid -n -f 50 -t 5000 -o short_video_" << ++count << ".h264";
	FILE* video;
	struct timeval time;
	if (gettimeofday(&time, NULL)) throw 3;
	system(vidCall.str()); //five second clip
	return;
	//video = fopen("short_video.h264", "r");
	//if (video = NULL) throw 1;
	//return tagFile(video, "SVid" + std::to_string(++count), time);
}

struct serial_t tagFile(FILE* file, std::string tag, struct timeval time){
	using namespace std;
	fseek (file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);
	char* buffer;
	buffer = malloc(size + tag.size() * 2 + 5);
	int index = 0;
	buffer[index++] = '<';
	tag.copy(buffer + index, tag.size(), 0);
	index += tag.size();
	buffer[index++] = '>';
	char * fgets(index, size, file);
	index += size;
	buffer[index++] = '<';
	buffer[index++] = '/';
	tag.copy(buffer + index, tag.size(), 0);
	index += tag.size();
	buffer[index] = '>';
	struct serial_t res;
	res.message = buffer;
	res.length = index;
	res.time = time;
	return res;
	
}