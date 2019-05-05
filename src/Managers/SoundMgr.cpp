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
                this->selectionSoundsDictionary[i][j] = -1;
            }
        }


	unsigned int sid;

        //background music
	std::string filename = "Sounds/Spacey.wav";
	if (this->reserveAudio(filename, true, sid)){
		std::cout << "background music loaded" << std::endl;
                backgroundMusicSource = sourceInfo[sid].source;
            this->loadAllSounds("backgroundmusic", "Sounds/Spacey.wav");
        }
	std::cout << "background music loaded" << std::endl;

//      default gunshot sound for all entities
    unsigned int gunshotsid;
    std::string gunshotfilename = "Sounds/gunshot.wav";
    if (this->reserveAudio(gunshotfilename, false, gunshotsid)){
            battleSoundSource = sourceInfo[gunshotsid].source;
            this->loadAllSounds("gunshot", "Sounds/gunshot.wav");
        }

//		default sound for when player takes damage
    unsigned int playerdamagesid;
    std::string playerdamagefilename = "Sounds/player_damage.wav";
    if (this->reserveAudio(playerdamagefilename, false, playerdamagesid)){
            playerDamageSource = sourceInfo[playerdamagesid].source;
            this->loadAllSounds("playerdamage", "Sounds/player_damage.wav");
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

	return;
}

void SoundMgr::loadLevel(void){

	return;
}


void SoundMgr::tick(double dtime){


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



bool SoundMgr::playSelectionSound(Entity381 et){

        if (et.soundFile == ""){
            std::cout << "There is no registered selection sounds for this entity type" << std::endl;
            return false; //there is no sound to play
        }
        this->playAudioSourceIndex(et.auioId);

        return true;
}


void SoundMgr::releaseLevel(void){

	return;
}

void SoundMgr::cleanup(void){
	return;
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


bool SoundMgr::setSound( ALuint audioID, Ogre::Vector3 position,
    Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
    bool playNow, bool forceRestart, float minGain ){
	return false;
}


bool SoundMgr::setListenerDisposition( Ogre::Vector3 position, Ogre::Vector3 velocity, Ogre::Quaternion orientation ){
	return false;
}

bool SoundMgr::loadAllSounds(std::string sound_type, std::string filename){

if(sound_type=="gunshot"){
	std::cout<<"gunshot"<<std::endl;
	sourcetemp = battleSoundSource;
	buffertemp = battleSoundBuffer;
	waveTemp = battleWaveInfo;}

if(sound_type=="playerdamage"){
	std::cout<<"pd"<<std::endl;
	sourcetemp = playerDamageSource;
	buffertemp = playerDamageBuffer;
	waveTemp = playerDamageInfo;}

if(sound_type=="backgroundmusic"){
	std::cout<<"bm"<<std::endl;
	sourcetemp = backgroundMusicSource;
	buffertemp = backgroundMusicBuffer;
	waveTemp = backgroundWaveInfo;}

std::cout<<"one initialzied"<<std::endl;
	alGenSources((ALuint)1, &this->sourcetemp);
	printError("Cannot generate source with id 1");

	alSourcef(this->sourcetemp, AL_PITCH, .95);
	printError("Source pitch");

	alSourcef(this->sourcetemp, AL_GAIN, 2);
	printError("Source Gain");

	alSource3f(this->sourcetemp, AL_POSITION, 0, 0, 0);
	printError("Source position");

	alSource3f(this->sourcetemp, AL_VELOCITY, 0, 0, 0);
	printError("Source velocity");

	alSourcei(this->sourcetemp, AL_LOOPING, AL_FALSE);
	printError("Source looping");

	alGenBuffers(1, &this->buffertemp);  /////
	printError("Buffer generation");

	std::string fqfn = getFQFNFromFilename(filename);
	std::cout << "SoundManager battleSound file: " << fqfn << " is being readied" << std::endl;
	if(fqfn == "")
		return false;

	this->waveTemp = WaveOpenFileForReading(fqfn.c_str());
	if(!this->waveTemp){
		std::cerr << "ERROR: Cannot open wave file for reading" << std::endl;
		return false;
	}
	int ret = WaveSeekFile(0, this->waveTemp);
	if (ret) {
		std::cerr << "ERROR: Cannot seek" << std::endl;
		return false;
	}
	char *tmpBuf = (char *) malloc(this->waveTemp->dataSize);
	if(!tmpBuf){
		std::cerr << "ERROR: in malloc" << std::endl;
		return false;
	}
	ret = WaveReadFile(tmpBuf, this->waveTemp->dataSize, this->waveTemp);
	if(ret != (int) this->waveTemp->dataSize){
		std::cerr << "ERROR: short read " << ret << " wanted: " << this->waveTemp->dataSize << std::endl;
		return false;
	}
	alBufferData(this->buffertemp,
			toALFormat(this->waveTemp->channels, this->waveTemp->bitsPerSample),
			tmpBuf, this->waveTemp->dataSize, this->waveTemp->sampleRate);
	if(printError("Failed to load bufferData") < 0){
		return false;
	}

	free(tmpBuf);

	alSourcei(this->sourcetemp, AL_BUFFER, this->buffertemp);
	printError("Source binding");

	printError("Playing");
		if(sound_type=="backgroundmusic"){
			playSelectedSound(background_music);}
	return true;
}

void SoundMgr::playSelectedSound(SoundTypes sound_type){
	switch(sound_type){
	case gunshot:
		alSourcePlay(battleSoundSource);
		break;
	case player_damage:
		alSourcePlay(playerDamageSource);
		break;
	case background_music:
		alSourcePlay(backgroundMusicSource);
		break;
	}
}








