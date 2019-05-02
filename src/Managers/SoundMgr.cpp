/*
 * SoundMgr.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: sushil
 */

#include <Engine.h>
#include <SoundMgr.h>
#include <stdlib.h>
#include <EntityMgr.h>

using namespace OgreSND;


SoundMgr::SoundMgr(Engine *eng): Mgr(eng){
	this->engine = eng;

}

SoundMgr::~SoundMgr(){

	std::cout << "Deleting Sound Manager" << std::endl;


	//Destroy sounds
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		if(alIsSource(this->sourceInfo[i].source)){
			alDeleteSources(1, &this->sourceInfo[i].source);
		}
	}

	//Destroy buffers
	for(int i = 0; i < OgreSND::maxAudioBuffers; i++){
		if(alIsBuffer(this->bufferInfo[i].buffer)){
			alDeleteBuffers(1, &this->bufferInfo[i].buffer);
		}
	}

	int ret;
	ret = alcMakeContextCurrent(NULL);
	if (!ret) {
		std::cerr << "Null current context" << std::endl;
	}
	alcDestroyContext(context);
	//printError("Destroy Context");

	//close device
	alcCloseDevice(device);
	//printError("Device close");
	std::cout << "Bye audio. ....   Sounds good, bye" << std::endl;
}

void SoundMgr::init(){
	initialize();
}

void SoundMgr::initialize(void){
	this->device = alcOpenDevice(NULL);
	if(!device){
		std::cerr << "Sound ERROR: Bye, could not open default sound device" << std::endl;
	}
	alGetError();
	this->context = alcCreateContext(this->device, NULL);
	if (!alcMakeContextCurrent(this->context)) {
		std::cerr << "Sound ERROR: Cannot make default context" << std::endl;
	}
	//this->buffersInfo.buffersInUseCount = 0;
	for(int i = 0; i < OgreSND::maxAudioBuffers; i++){
		this->bufferInfo[i].buffer = i+1; // this is because openAl returns true for alIsBuffer(0) no matter what!
		//I'm also using bufferFilename == "" to check if the buffer is in use.
		this->bufferInfo[i].bufferFilename = "";
	}

	//this->sourcesInfo.sourcesInUseCount = 0;
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		this->sourceInfo[i].source = 0;
		this->sourceInfo[i].inUse = false;
                this->sourceDictionary.push_back("");
	}

        isEnabled = true;

        //initialize vectors
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < soundPerEnt; j++){
                //this->battleSoundsDictionary[i][j] = -1;
                //this->creationSoundsDictionary[i][j] = -1;
                this->selectionSoundsDictionary[i][j] = -1;
            }
        }


	unsigned int sid;

        //background music
	std::string filename = "Sounds/Spacey.wav";
	if (this->reserveAudio(filename, true, sid)){
		std::cout << "background music loaded" << std::endl;
                backgroundMusicSource = sourceInfo[sid].source;
                this->loadStartBackground();
        }
	std::cout << "background music loaded" << std::endl;

//      default gunshot sound for all entities
    unsigned int gunshotsid;
    std::string gunshotfilename = "Sounds/gunshot.wav";
    if (this->reserveAudio(gunshotfilename, false, gunshotsid)){
            battleSoundSource = sourceInfo[gunshotsid].source;
//            this->loadStartGunshot();
//              this->loadSound(battleWaveInfo, *battleSoundSource, *battleSoundBuffer, battleSoundBuffer, battleSoundSource, battleSoundFilename); // @suppress("Invalid arguments")
        }

//		default sound for when player takes damage
    unsigned int playerdamagesid;
    std::string playerdamagefilename = "Sounds/player_damage.wav";
    if (this->reserveAudio(playerdamagefilename, false, playerdamagesid)){
            playerDamageSource = sourceInfo[gunshotsid].source;
            this->loadPlayerDamage();
        }

	return;

}


void SoundMgr::enable(){
    isEnabled = true;
    resumeBackground();
}

void SoundMgr::disable(){
    isEnabled = false;
    stopAllAudio();
    stopBackground();
}


bool SoundMgr::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	tick(evt.timeSinceLastFrame);
	return true;
}
bool SoundMgr::frameStarted(const Ogre::FrameEvent& evt){
	return true;
}
bool SoundMgr::frameEnded(const Ogre::FrameEvent& evt){
	return true;
}



void SoundMgr::crosslink(void){
//	syncListenerToCamera();
	return;
}

void SoundMgr::loadLevel(void){
//	syncListenerToCamera();
	//load sounds, bind buffers, start background music
	//read sound files

	//load background, start, loop
	//loadStartBackground();


	return;
}
double static tmpT = 0.0;
bool static paused = false;


void SoundMgr::attachSelectedNodeToSoundIndex(Entity381 *ent, unsigned int index){

}

void SoundMgr::tick(double dtime){

//	playGunshot();
//	syncListenerToCamera();

        //selection sound
		for(std::vector<Entity381 *>::const_iterator it = engine->entityMgr->entities.begin(); it != engine->entityMgr->entities.end(); ++it){
           if ((*it)->isSelected && !(*it)->didSelectSoundPlay){
        	   playSelectionSound(*(*it));
        	   (*it)->didSelectSoundPlay = true;
           }
           else if (!(*it)->isSelected && (*it)->didSelectSoundPlay){
        	   (*it)->didSelectSoundPlay = false;
           }
        }

}

        //this was for moving sound but playing sound for all moving objects does not seem to be a good idea
        //copySoundState();



bool SoundMgr::playSelectionSound(Entity381 et){
        Ogre::Vector3 pos = et.position;

        if (et.soundFile == ""){
            std::cout << "There is no registered selection sounds for this entity type" << std::endl;
            return false; //there is no sound to play
        }
        this->playAudioSourceIndex(et.auioId);
//        setSoundPosition(sourceInfo[et.auioId].source, pos);

        return true;
}


void SoundMgr::releaseLevel(void){
	// release stuff loaded for this level
	return;
}

void SoundMgr::cleanup(void){
	return;
}

void SoundMgr::printAudioDevices(const ALCchar *devices){

	const ALCchar *device = devices;
	const ALCchar *next   = devices+1;
	size_t len = 0;

	std::cout << "Devices list:" << std::endl;
	while(device && *device != '\0' && next && *next != '\0') {
		std::cout << device << std::endl;
		len = strlen(device);
		device += len + 1;
		next   += len + 2;
	}
	std::cout << "------------------" << std::endl;
}

int SoundMgr::printError(const char *ermsg){
	ALCenum error = alGetError();
	if (error != AL_NO_ERROR){
		std::cerr << "SoundManager: ERROR: "<< ermsg << std::endl;
		return -1;
	}
	return 0;
}

inline ALenum SoundMgr::toALFormat(short channels, short samples) {
	bool stereo = (channels > 1);
	switch (samples){
	case 16:
		if (stereo) {
			return AL_FORMAT_STEREO16;
		} else {
			return AL_FORMAT_MONO16;
		}

	case 8:
		if (stereo) {
			return AL_FORMAT_STEREO8;
		} else {
			return AL_FORMAT_MONO8;
		}

	default:
		return -1;

	}
}


int SoundMgr::getBufferId(std::string filename){
	// two cases
	//1. sound is already in a buffer, then return the buffer's index
	//2. sound is not already in a buffer, then load it into an unused buffer index and return it
	//Case 1:
	for (int i = 0; i < OgreSND::maxAudioBuffers; i++){
		if (this->bufferInfo[i].bufferFilename == filename){
			return i;
		}
	}
	std::cout << "Cannot find buffer, attempting to load file: " << filename << std::endl;
	//Case 2
	for (int i = 0; i < OgreSND::maxAudioBuffers; i++){
		if (this->bufferInfo[i].bufferFilename == ""){
			if (loadAudio(filename, i)){
				return i;
			} else {
				std::cerr << "getBufferId::cannot load audio from file: " << filename << std::endl;
				return -1;
			}
		}
	}

	return -1;
}

int SoundMgr::getEmptySourceIndex(){
	for (int i = 0; i < OgreSND::maxAudioSources; i++){
		if (!this->sourceInfo[i].inUse){
			return i;
		}
	}
	return -1;
}

bool SoundMgr::registerSelection(Entity381 et, std::string filename){
    unsigned int sid;
    if (this->reserveAudio(filename, false, sid)){
                int lastIndex = -1;
                for (int i = 0; i < soundPerEnt; i++){
                    if (this->selectionSoundsDictionary[et.auioId][i] == -1){
                        lastIndex = i;
                        break;
                    }
                }
                if (lastIndex == -1){ //all permitted number of sounds for this type are already assigned
                    std::cout << "Could not register new sound, max allowed number per entity reached" << std::endl;
                    return false;
                }
                this->selectionSoundsDictionary[et.auioId][lastIndex] = sid;
                alSourcei(this->sourceInfo[sid].source, AL_REFERENCE_DISTANCE, 2000.0f);
                alSourcei(this->sourceInfo[sid].source, AL_MAX_DISTANCE, 8000.0f);

                sourceDictionary[sid] = filename;
                et.soundFile = filename;

                return true;
    }
    else
        return false;
}

bool SoundMgr::reserveAudio(std::string filename, bool loop, unsigned int &sourceInfoIndex){
//bool SoundMgr::reserveAudio(std::string filename, bool loop){ //

	alGetError();
	int bufferId = this->getBufferId(filename); // if buffer not generated - it is generated in loadAudio
	if(bufferId < 0) {
		std::cout << "GetBufferId: Error loading: " << filename << std::endl;
		std::cout << "All buffers in use, you will need to release buffers before you can get this sound to play: " << filename << std::endl;
		return false;
	}

	int index = getEmptySourceIndex();
	if (index < 0) {
		std::cout << "All sources in use, you will need to release sources before you can get this sound to play: " << filename << std::endl;
		return false;
	}
	if (!alIsSource(this->sourceInfo[index].source)){
		alGenSources(1, &this->sourceInfo[index].source);
		if(printError("ReserveAudio::Cannot Generate source") < 0){
			return false;
		}
		std::cout << "Generated Source " << std::endl;
	}

	resetSource(this->sourceInfo[index].source);

	if(loop){
		alSourcei(this->sourceInfo[index].source, AL_LOOPING, AL_TRUE);
		if(printError("Source looping") < 0){
			return false;
		}
	}
	/*******************************************************************************************/
	sourceInfoIndex = index; // to be returned**************************************
	/*******************************************************************************************/
	this->sourceInfo[index].inUse = true;
	alSourcei(this->sourceInfo[sourceInfoIndex].source, AL_BUFFER, this->bufferInfo[bufferId].buffer);
	if (printError("Error in binding source to buffer for ") < 0){
		return false;
	}
	return true; //return error code
}

bool SoundMgr::resetSource(ALuint sourceId){

	alSourcef(sourceId, AL_PITCH, 1);
	if (printError("Source pitch") < 0)
		return false;

	alSourcef(sourceId, AL_GAIN, 1);
	if(printError("Source Gain") < 0)
		return false;

	alSource3f(sourceId, AL_POSITION, 0, 0, 0);
	if(printError("Source position") < 0)
		return false;

	alSource3f(sourceId, AL_VELOCITY, 0, 0, 0);
	if (printError("Source velocity") < 0)
		return false;

	return true;
}

/**
 * Releases a source name. First finds it souceInfo, stopsAudio playing if any, then deletes the source
 *
 *
 */
bool SoundMgr::releaseSourceIndex(int sid){

	ALuint source = this->sourceInfo[sid].source;
	if (! alIsSource(source)){
		std::cerr << "ReleaseSource:: is not a source!" << source << std::endl;
		return false;
	}
	if(!stopAudio(source)){
		std::cerr << "ReleaseSource:: Could not stop audio before release" << source << std::endl;
		return false;
	}
	alDeleteSources(1, &this->sourceInfo[sid].source);
	if (printError("ReleaseAudio::Cannot delete source") < 0){
		return false;
	}
	this->sourceInfo[sid].inUse = false;
	return true;
}

bool SoundMgr::releaseSource(ALuint audioId){
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		if (this->sourceInfo[i].source == audioId){
			return releaseSourceIndex(i);
		}
	}
	return false;
}



std::string SoundMgr::getFQFNFromFilename(std::string filename){

	return filename;
}

//specific to FastEcslsent------------------------------------------------------------------------------------

bool SoundMgr::stopBackground(){

	alSourceStop(this->backgroundMusicSource);
	if (printError("Stop background music") < 0){
		return false;
	} else {
		return true;
	}


}

bool SoundMgr::pauseBackground(){
	alSourcePause(this->backgroundMusicSource);
	if(printError("PauseBackground Source") < 0){
		return false;
	} else {
		return true;
	}
}

bool SoundMgr::resumeBackground(){
	alSourcePlay(this->backgroundMusicSource);
	if(printError("Resume background Source") < 0){
		return false;
	} else {
		return true;
	}
}

bool SoundMgr::loadAudio(std::string filename, int index){
	alGetError();//init errors
	std::string fqfn = getFQFNFromFilename(filename);
	std::cout << "SoundManager Music file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->bufferInfo[index].wave = WaveOpenFileForReading(filename.c_str());

	if(!this->bufferInfo[index].wave){
		std::cerr << "SoundMgr::loadAudio::ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, this->bufferInfo[index].wave);
	if (ret) {
		std::cerr << "SoundMgr::loadAudio::ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(this->bufferInfo[index].wave->dataSize);
	//this->backgroundBufferData = (char *) malloc(this->backgroundWaveInfo->dataSize);
	if(!tmpBuf){
		std::cerr << "SoundMgr::loadAudio::ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, this->bufferInfo[index].wave->dataSize, this->bufferInfo[index].wave);
	if(ret != (int) this->bufferInfo[index].wave->dataSize){
		std::cerr << "ERROR: SoundMgr::loadAudio: short read " << ret << " wanted: " << this->bufferInfo[index].wave->dataSize << std::endl;
		return false;
	}

	if(!alIsBuffer(this->bufferInfo[index].buffer) || this->bufferInfo[index].bufferFilename == ""){
		//bufferFilename == "" means not a buffer
		alGenBuffers(1, &this->bufferInfo[index].buffer);
		if (printError("Cannot generate buffers") < 0) {
			return false;
		}
		std::cout << "Generated Buffer " << std::endl;
	}

	alBufferData(this->bufferInfo[index].buffer,
			toALFormat(this->bufferInfo[index].wave->channels, this->bufferInfo[index].wave->bitsPerSample),
			tmpBuf, this->bufferInfo[index].wave->dataSize, this->bufferInfo[index].wave->sampleRate);
	free(tmpBuf);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	this->bufferInfo[index].bufferFilename = filename;

	return true;
}



// Returns true if we can play the sound. Rewinds sound if already playing and forceRestart is true,
// false if error
bool SoundMgr::playAudio(ALuint audioId, bool forceRestart ){
        if (!this->isEnabled)
                return false;
	if (!alIsSource(audioId))
		return false;

	ALint source_state;
	alGetSourcei(audioId, AL_SOURCE_STATE, &source_state);
	if(printError("Get source state") < 0)
		return false;
	if(source_state == AL_PLAYING){
		if (forceRestart){
			stopAudio(audioId);
			if (printError("PlayAudio:: Could not stop already playing song") < 0){
				return false;
			}
                        alSourcePlay(audioId);
		}
		return true;
	}
	alSourcePlay(audioId);
	if(printError("PlayAudio:: Could not play") < 0)
		return false;
	return true;
}

bool SoundMgr::playAudio(ALuint audioId){
	return playAudio(audioId, false);
}

bool SoundMgr::playAudioSourceIndex(int sid, bool forceRestart){
	return playAudio(this->sourceInfo[sid].source, forceRestart);
}

bool SoundMgr::playAudioSourceIndex(int sid){
	return playAudio(this->sourceInfo[sid].source, false);
}

bool SoundMgr::stopAudio(ALuint audioId){
	if (alIsSource(audioId)){
		alSourceStop(audioId);
		if (printError("StopAudio::cannot stop source: " + audioId) < 0){
			return false;
		}
	} else {
		std::cerr << "StopAudio:: Is not a source: " << audioId << std::endl;
		return false;
	}
	return true;
}

bool SoundMgr::stopAudioSourceIndex(int sid){
        return this->stopAudio(this->sourceInfo[sid].source);
}

bool SoundMgr::isAudioPlaying(ALuint audioId){
    	if (!alIsSource(audioId))
		return false;

	ALint source_state;
	alGetSourcei(audioId, AL_SOURCE_STATE, &source_state);
	if(printError("Get source state") < 0)
		return false;
	if(source_state == AL_PLAYING){
		return true;
	}
        if(printError("PlayAudio:: Could not play") < 0)
		return false;
}

bool SoundMgr::stopAllAudio( void ){
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		stopAudio(this->sourceInfo[i].source);
	}
	return true;
}

bool SoundMgr::pauseAudioSourceIndex(int sid){

	pauseAudio(this->sourceInfo[sid].source);
	return true;
}
bool SoundMgr::pauseAudio(ALuint audioId ){
	if(!alIsSource(audioId))
		return false;
	alSourcePause(audioId);
	if (printError("PauseAudio::Cannot pause: " + audioId) < 0){
		return false;
	}
	return true;
}

bool SoundMgr::pauseAllAudio( void ){
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		pauseAudio(this->sourceInfo[i].source);
	}
	return true;
}

bool SoundMgr::resumeAudio(ALuint audioId){
	return playAudio(audioId);
}

bool SoundMgr::resumeAllAudio( void ){
	for(int i = 0; i < OgreSND::maxAudioSources; i++){
		playAudio(this->sourceInfo[i].source);
	}
	return true;
}

bool SoundMgr::setSoundPosition(ALuint audioId, Ogre::Vector3 position ){

	alSourcef(audioId, AL_GAIN, 1.0);
	if(printError("Source Gain") < 0)
		return false;


	alSource3f(audioId, AL_POSITION, position.x, position.y, position.z);
	if (printError("SetSoundPosition::Source position") < 0) return false;
	return true;;
}


bool SoundMgr::setSoundDisposition( ALuint audioId, Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Vector3 direction ){
	alSource3f(audioId, AL_POSITION, position.x, position.y, position.z);
	if (printError("SetSoundDisPosition::Source position") < 0) return false;

	alSource3f(audioId, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	if (printError("SetSoundDisPosition::Source velocity") < 0) return false;

	return true;
}


bool SoundMgr::setSound( ALuint audioID, Ogre::Vector3 position,
    Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
    bool playNow, bool forceRestart, float minGain ){
	return false;
}


bool SoundMgr::setListenerDisposition( Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Quaternion orientation ){
	return false;
}

bool SoundMgr::initActionSounds(Entity381* et){
        //registering all sounds
		std::string gunshotFilename = "Sounds/gunshot.wav";
        std::string selection2Filename = "data/watercraft/sounds/GoodDay.wav";
        //std::string createShipFilename = "data/watercraft/sounds/boatMoving.wav";
        //std::string createBuildingFilename = "data/watercraft/sounds/clong.wav";
            //this->registerBattleSound(et, battleFilename);
                        this->registerSelection(*et, gunshotFilename);

                //this->registerCreate(et, createShipFilename);


        return true;
}
void SoundMgr::playGunshot(){
	alSourcePlay(this->battleSoundSource);
//	stopAudio(this->battleSoundSource);
}

void SoundMgr::playPlayerDamage(){
	alSourcePlay(this->playerDamageSource);
//	stopAudio(this->battleSoundSource);
}


bool SoundMgr::loadStartGunshot(){
	//WaveInfo *wave;

	alGenSources((ALuint)1, &this->battleSoundSource);
	printError("Cannot generate source with id 1");

	alSourcef(this->battleSoundSource, AL_PITCH, .95);
	printError("Source pitch");

	alSourcef(this->battleSoundSource, AL_GAIN, 2);
	printError("Source Gain");

	alSource3f(this->battleSoundSource, AL_POSITION, 0, 0, 0);
	printError("Source position");

	alSource3f(this->battleSoundSource, AL_VELOCITY, 0, 0, 0);
	printError("Source velocity");

	alSourcei(this->battleSoundSource, AL_LOOPING, AL_FALSE);
	printError("Source looping");

	alGenBuffers(1, &this->battleSoundBuffer);  /////
	printError("Buffer generation");

	std::string fqfn = getFQFNFromFilename(OgreSND::battleSoundFilename);
	std::cout << "SoundManager battleSound file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->battleWaveInfo = WaveOpenFileForReading(fqfn.c_str());
	if(!this->battleWaveInfo){
		std::cerr << "ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, this->battleWaveInfo);
	if (ret) {
		std::cerr << "ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(this->battleWaveInfo->dataSize);
	//this->backgroundBufferData = (char *) malloc(this->backgroundWaveInfo->dataSize);
	if(!tmpBuf){
		std::cerr << "ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, this->battleWaveInfo->dataSize, this->battleWaveInfo);
	if(ret != (int) this->battleWaveInfo->dataSize){
		std::cerr << "ERROR: short read " << ret << " wanted: " << this->battleWaveInfo->dataSize << std::endl;
		return false;
	}
	alBufferData(this->battleSoundBuffer,
			toALFormat(this->battleWaveInfo->channels, this->battleWaveInfo->bitsPerSample),
			tmpBuf, this->battleWaveInfo->dataSize, this->battleWaveInfo->sampleRate);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	free(tmpBuf);

	alSourcei(this->battleSoundSource, AL_BUFFER, this->battleSoundBuffer);
	printError("Source binding");

	printError("Playing");
//	printError("Playing");


	return true;
}

bool SoundMgr::loadStartBackground(){
	//WaveInfo *wave;


	alGenSources((ALuint)1, &this->backgroundMusicSource);
	printError("Cannot generate source with id 1");

	alSourcef(this->backgroundMusicSource, AL_PITCH, 1);
	printError("Source pitch");

	alSourcef(this->backgroundMusicSource, AL_GAIN, 2);
	printError("Source Gain");

	alSource3f(this->backgroundMusicSource, AL_POSITION, 0, 0, 0);
	printError("Source position");

	alSource3f(this->backgroundMusicSource, AL_VELOCITY, 0, 0, 0);
	printError("Source velocity");

	alSourcei(this->backgroundMusicSource, AL_LOOPING, AL_TRUE);
	printError("Source looping");

	alGenBuffers(1, &this->backgroundMusicBuffer);
	printError("Buffer generation");

	std::string fqfn = getFQFNFromFilename(OgreSND::backgroundMusicFilename);
	std::cout << "SoundManager backgroundMusic file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->backgroundWaveInfo = WaveOpenFileForReading(fqfn.c_str());
	if(!this->backgroundWaveInfo){
		std::cerr << "ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, this->backgroundWaveInfo);
	if (ret) {
		std::cerr << "ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(this->backgroundWaveInfo->dataSize);
	//this->backgroundBufferData = (char *) malloc(this->backgroundWaveInfo->dataSize);
	if(!tmpBuf){
		std::cerr << "ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, this->backgroundWaveInfo->dataSize, this->backgroundWaveInfo);
	if(ret != (int) this->backgroundWaveInfo->dataSize){
		std::cerr << "ERROR: short read " << ret << " wanted: " << this->backgroundWaveInfo->dataSize << std::endl;
		return false;
	}
	alBufferData(this->backgroundMusicBuffer,
			toALFormat(this->backgroundWaveInfo->channels, this->backgroundWaveInfo->bitsPerSample),
			tmpBuf, this->backgroundWaveInfo->dataSize, this->backgroundWaveInfo->sampleRate);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	free(tmpBuf);

	alSourcei(this->backgroundMusicSource, AL_BUFFER, this->backgroundMusicBuffer);
	printError("Source binding");

//	alSourcePlay(this->backgroundMusicSource);
	printError("Playing");


	return true;
}

bool SoundMgr::loadPlayerDamage(){
	//WaveInfo *wave;


	alGenSources((ALuint)1, &this->playerDamageSource);
	printError("Cannot generate source with id 1");

	alSourcef(this->playerDamageSource, AL_PITCH, 1);
	printError("Source pitch");

	alSourcef(this->playerDamageSource, AL_GAIN, 2);
	printError("Source Gain");

	alSource3f(this->playerDamageSource, AL_POSITION, 0, 0, 0);
	printError("Source position");

	alSource3f(this->playerDamageSource, AL_VELOCITY, 0, 0, 0);
	printError("Source velocity");

	alSourcei(this->playerDamageSource, AL_LOOPING, AL_FALSE);
	printError("Source looping");

	alGenBuffers(1, &this->playerDamageBuffer);
	printError("Buffer generation");

	std::string fqfn = getFQFNFromFilename(OgreSND::playerDamageFilename);
	std::cout << "SoundManager backgroundMusic file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->playerDamageInfo = WaveOpenFileForReading(fqfn.c_str());
	if(!this->playerDamageInfo){
		std::cerr << "ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, this->playerDamageInfo);
	if (ret) {
		std::cerr << "ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(this->playerDamageInfo->dataSize);
	//this->backgroundBufferData = (char *) malloc(this->playerDamageInfo->dataSize);
	if(!tmpBuf){
		std::cerr << "ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, this->playerDamageInfo->dataSize, this->playerDamageInfo);
	if(ret != (int) this->playerDamageInfo->dataSize){
		std::cerr << "ERROR: short read " << ret << " wanted: " << this->playerDamageInfo->dataSize << std::endl;
		return false;
	}
	alBufferData(this->playerDamageBuffer,
			toALFormat(this->playerDamageInfo->channels, this->playerDamageInfo->bitsPerSample),
			tmpBuf, this->playerDamageInfo->dataSize, this->playerDamageInfo->sampleRate);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	free(tmpBuf);

	alSourcei(this->playerDamageSource, AL_BUFFER, this->playerDamageBuffer);
	printError("Source binding");

	alSourcePlay(this->playerDamageSource);
	printError("Playing");


	return true;
}

bool SoundMgr::loadSound(WaveInfo *Info, ALuint *sourcepoint, ALuint *bufferpoint, ALuint buffer, ALuint source, std::string filename){
	//WaveInfo *wave;

	alGenSources((ALuint)1, sourcepoint);
	printError("Cannot generate source with id 1");

	alSourcef(source, AL_PITCH, 1);
	printError("Source pitch");

	alSourcef(source, AL_GAIN, 2);
	printError("Source Gain");

	alSource3f(source, AL_POSITION, 0, 0, 0);
	printError("Source position");

	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	printError("Source velocity");

	alSourcei(source, AL_LOOPING, AL_FALSE);
	printError("Source looping");

	alGenBuffers(1, bufferpoint);
	printError("Buffer generation");

	std::string fqfn = getFQFNFromFilename(filename); //soundmgr filename
	std::cout << "SoundManager backgroundMusic file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->playerDamageInfo = WaveOpenFileForReading(fqfn.c_str());
	if(!this->playerDamageInfo){
		std::cerr << "ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, Info);
	if (ret) {
		std::cerr << "ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(Info->dataSize);
	if(!tmpBuf){
		std::cerr << "ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, Info->dataSize, Info);
	if(ret != (int) Info->dataSize){
		std::cerr << "ERROR: short read " << ret << " wanted: " << Info->dataSize << std::endl;
		return false;
	}
	alBufferData(buffer,
			toALFormat(Info->channels, Info->bitsPerSample),
			tmpBuf, Info->dataSize, Info->sampleRate);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	free(tmpBuf);

	alSourcei(source, AL_BUFFER, buffer);
	printError("Source binding");

	alSourcePlay(source);
	printError("Playing");


	return true;
}





