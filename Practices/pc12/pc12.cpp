#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MaxVid = 100;

typedef enum { Poor, Regular, Good, Extra } tQuality;

const string Names[4] = { "Poor", "Regular", "Good", "Extra" };

struct tVideo {
	string name;
	tQuality quality = Extra;
	int kiloBytes = 0;
};

typedef tVideo tVideoArray[MaxVid];

struct tVideoList {
	tVideoArray videos;
	int counter = 0;
};

const int MaxDisk = 20;

struct tDisk {
	string id;
	int capacity = 0; // kiloBytes
	int available = 0;
	tQuality quality = Extra;
	tVideoList videoList;
};

typedef tDisk tDiskArray[MaxDisk];

struct tStorage {
	tDiskArray disks;
	int counter = 0;
};

bool load(tStorage& storage);
bool load(tVideoList& toAllocate);
void delVideo(tVideoList& toAllocate, int index);
tVideo getNext(tVideoList& toAllocate);
int find(const tStorage& storage, tVideo video);
void assign(tStorage& storage, tVideoList& toAllocate, tVideoList& unallocated);
void display(const tVideoList& toAllocate);
void display(const tStorage& storage);
tQuality charToQuality(char qualityChar);
char qualityToChar(tQuality quality);

int main() {
	tStorage storage;
	tVideoList toAllocate, unallocated;

	if (load(storage)) {
		if (load(toAllocate)) {
			assign(storage, toAllocate, unallocated);
			display(storage);
			cout << "Videos that couldn't be stored..." << endl;
			display(unallocated);
		}
		else
			cout << "Sorry, the list of videos couldn't be loaded!" << endl;
	}
	else
		cout << "Sorry, the storage couldn't be loaded!" << endl;

	return 0;
}

bool load(tStorage& storage) {
	bool ok = false;
	tDisk disk;
	ifstream file;
	char qualityChar;
	string str;

	storage.counter = 0;
	file.open("disks.txt");
	if (file.is_open()) {
		ok = true;
		file >> str;
		while ((str != "XXX") && (storage.counter < MaxDisk)) {
			disk.id = str;
			file >> qualityChar;
			disk.quality = charToQuality(qualityChar);
			file >> disk.capacity;
			disk.available = disk.capacity;
			storage.disks[storage.counter] = disk;
			storage.counter++;
			file >> str;
		}
		file.close();
	}

	return ok;
}

bool load(tVideoList& toAllocate) {
	bool ok = false;
	tVideo video;
	char tmpChar;

	toAllocate.counter = 0;
	ifstream inputFile("videos.txt");
	if (inputFile.is_open()) {
		ok = true;
		inputFile >> tmpChar;
		while ((tmpChar != '0') && (toAllocate.counter < MaxVid)) {
			video.quality = charToQuality(tmpChar);
			inputFile >> video.name;
			inputFile >> video.kiloBytes;
			toAllocate.videos[toAllocate.counter] = video;
			toAllocate.counter++;
			inputFile >> tmpChar;
		}
		inputFile.close();
	}
	return ok;
}

void delVideo(tVideoList& list, int index) { // Deletes from the list the video in index (it do exists)...
	// We just put the last one in index
	for (int i = index + 1; i < list.counter; i++) {
		list.videos[i - 1] = list.videos[i]; 
	}
	list.counter--;
}

tVideo getNext(tVideoList& toAllocate) { // Returns the biggest video... (toAllocate has videos)
	tVideo nextVideo, video;
	int max = -1;
	for (int i = 0; i < toAllocate.counter; i++){
		video = toAllocate.videos[i];
		if (video.kiloBytes > max){
			nextVideo = video;
			max = video.kiloBytes;
		}
	}
	return nextVideo;
}

int find(const tStorage& storage, tVideo video) { // Tries to find a suitable disk for the video...
	tDisk disk;
	int index = -1;
	bool found = false;
	int i = 0;
	while (i < storage.counter && !found){
		disk = storage.disks[i];
		if (disk.quality == video.quality && (video.kiloBytes <= disk.available)){	// Same quality, enough capacity
			index = i;
			found = true;
		}
		i++;
	}
	return index;
}

int find(const tVideoList& videoArr, tVideo target) { 
	tVideo video;
	int index = -1, i = 0;
	bool found = false;
	while (i < videoArr.counter && !found){
		video = videoArr.videos[i];
		if (video.name == target.name){		// Same video
			index = i;
			found = true;
		}
		i++;
	}
	return index;
}

void assign(tStorage& storage, tVideoList& toAllocate, tVideoList& unallocated) { // Processes the list of videos to allocate...
	// Returns the storage with the allocated videos, toAllocate empty and the list of unallocated
	tVideo video;
	int index, diskIdx;
	int nVideos = toAllocate.counter;
	for (int i = 0; i < nVideos; i++){
		video = getNext(toAllocate);
		index = find(toAllocate, video);

		delVideo(toAllocate, index);
		diskIdx = find(storage, video);
		if (diskIdx != -1){
			storage.disks[diskIdx].available -= video.kiloBytes;
			index = storage.disks[diskIdx].videoList.counter;
			storage.disks[diskIdx].videoList.videos[index] = video;
			storage.disks[diskIdx].videoList.counter++;
		} else {
			unallocated.videos[unallocated.counter] = video;
			unallocated.counter++;
		}
	}
}

void display(const tVideoList& list) { // Displays the list of videos...
	for (int i = 0; i < list.counter; i++)
		cout << "     " << qualityToChar(list.videos[i].quality) << " "
		<< list.videos[i].name << " " << list.videos[i].kiloBytes << " Kbytes" << endl;
	cout << endl;
}

void display(const tStorage& storage) {
	for (int i = 0; i < storage.counter; i++) {
		cout << storage.disks[i].id << " (" << Names[storage.disks[i].quality] << " quality)"
			<< " Disk usage: " << storage.disks[i].capacity - storage.disks[i].available
			<< "/" << storage.disks[i].capacity << endl;
		display(storage.disks[i].videoList);
	}
}

tQuality charToQuality(char qualityChar) {
	tQuality quality = Poor;

	if (qualityChar == 'R')
		quality = Regular;
	else if (qualityChar == 'G')
		quality = Good;
	else if (qualityChar == 'E')
		quality = Extra;

	return quality;
}

char qualityToChar(tQuality quality) {
	char qualityChar = 'P';

	if (quality == Regular)
		qualityChar = 'R';
	else if (quality == Good)
		qualityChar = 'G';
	else if (quality == Extra)
		qualityChar = 'E';

	return qualityChar;
}
