#include <Pineapple/Sound/SoundPool/SoundSP.h>
#include <Pineapple/Sound/SoundPool/BindingEffectSP.h>
#include <Pineapple/Sound/SoundPool/EffectSP.h>
#include <Pineapple/Sound/SoundPool/BindingMusicSP.h>
#include <Pineapple/Sound/SoundPool/MusicSP.h>
#include <Pineapple/Platform/Android/AndroidBridge.h>
#include <Pineapple/Platform/Android/AndroidJNI.h>

std::unique_ptr<pa::Sound> pa::MakeInternal::sound(const pa::FileSystem& fileSystem)
{
	return std::make_unique<pa::SoundPool>(fileSystem);
}

namespace
{
	pa::BindingEffectSP g_bindingEffectSP;
	pa::BindingMusicSP g_bindingMusicSP;
}

pa::SoundPool::SoundPool(const pa::FileSystem& fileSystem)
	: pa::Sound(fileSystem)
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();
	jclass localClass;

	localClass = pa::AndroidJNI::findClass("com.pineapple.sound.paSoundPool");
	PA_ASSERTF(localClass != nullptr, "Could not find required paSoundPool class");
	g_bindingEffectSP.classObject = reinterpret_cast<jclass>(env->NewGlobalRef(localClass));

	localClass = pa::AndroidJNI::findClass("com.pineapple.sound.paMediaPlayer");
	PA_ASSERTF(localClass != nullptr, "Could not find required paMediaPlayer class");
	g_bindingMusicSP.classObject = reinterpret_cast<jclass>(env->NewGlobalRef(localClass));

	g_bindingEffectSP.startup =  env->GetStaticMethodID(g_bindingEffectSP.classObject, "startup", "(Landroid/content/Context;)V");
	PA_ASSERTF(g_bindingEffectSP.startup != nullptr, "Could not find required paSoundPool.startup method");

	g_bindingEffectSP.shutdown = env->GetStaticMethodID(g_bindingEffectSP.classObject, "shutdown", "()V");
	PA_ASSERTF(g_bindingEffectSP.shutdown != nullptr, "Could not find required paSoundPool.shutdown method");

	g_bindingEffectSP.load =     env->GetStaticMethodID(g_bindingEffectSP.classObject, "load", "(Ljava/lang/String;)I");
	PA_ASSERTF(g_bindingEffectSP.load != nullptr, "Could not find required paSoundPool.load method");

	g_bindingEffectSP.unload =   env->GetStaticMethodID(g_bindingEffectSP.classObject, "unload", "(I)V");
	PA_ASSERTF(g_bindingEffectSP.unload != nullptr, "Could not find required paSoundPool.unload method");

	g_bindingEffectSP.play =     env->GetStaticMethodID(g_bindingEffectSP.classObject, "play", "(I)I");
	PA_ASSERTF(g_bindingEffectSP.play != nullptr, "Could not find required paSoundPool.play method");


	g_bindingMusicSP.startup =  env->GetStaticMethodID(g_bindingMusicSP.classObject, "startup", "(Landroid/content/Context;)V");
	PA_ASSERTF(g_bindingMusicSP.startup != nullptr, "Could not find required paMediaPlayer.startup method");

	g_bindingMusicSP.shutdown = env->GetStaticMethodID(g_bindingMusicSP.classObject, "shutdown", "()V");
	PA_ASSERTF(g_bindingMusicSP.shutdown != nullptr, "Could not find required paMediaPlayer.shutdown method");

	g_bindingMusicSP.load =     env->GetStaticMethodID(g_bindingMusicSP.classObject, "load", "(Ljava/lang/String;)I");
	PA_ASSERTF(g_bindingMusicSP.load != nullptr, "Could not find required paMediaPlayer.load method");

	g_bindingMusicSP.unload =   env->GetStaticMethodID(g_bindingMusicSP.classObject, "unload", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.unload != nullptr, "Could not find required paMediaPlayer.unload method");

	g_bindingMusicSP.play =     env->GetStaticMethodID(g_bindingMusicSP.classObject, "play", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.play != nullptr, "Could not find required paMediaPlayer.play method");

	g_bindingMusicSP.loop =     env->GetStaticMethodID(g_bindingMusicSP.classObject, "loop", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.loop != nullptr, "Could not find required paMediaPlayer.loop method");

	g_bindingMusicSP.stop =     env->GetStaticMethodID(g_bindingMusicSP.classObject, "stop", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.stop != nullptr, "Could not find required paMediaPlayer.stop method");

	g_bindingMusicSP.pause =    env->GetStaticMethodID(g_bindingMusicSP.classObject, "pause", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.pause != nullptr, "Could not find required paMediaPlayer.pause method");

	g_bindingMusicSP.resume =   env->GetStaticMethodID(g_bindingMusicSP.classObject, "resume", "(I)V");
	PA_ASSERTF(g_bindingMusicSP.resume != nullptr, "Could not find required paMediaPlayer.resume method");

	env->CallStaticVoidMethod(g_bindingEffectSP.classObject, g_bindingEffectSP.startup, AndroidBridge::getNativeActivity()->clazz);
	pa::AndroidJNI::handleExceptions();

	env->CallStaticVoidMethod(g_bindingMusicSP.classObject, g_bindingMusicSP.startup, AndroidBridge::getNativeActivity()->clazz);
	pa::AndroidJNI::handleExceptions();
}

pa::SoundPool::~SoundPool()
{
	auto env = pa::AndroidJNI::attachCurrentThreadIfNeeded();

	env->CallStaticVoidMethod(g_bindingEffectSP.classObject, g_bindingEffectSP.shutdown);
	pa::AndroidJNI::handleExceptions();

	env->CallStaticVoidMethod(g_bindingMusicSP.classObject, g_bindingMusicSP.shutdown);
	pa::AndroidJNI::handleExceptions();

	env->DeleteGlobalRef(g_bindingEffectSP.classObject);
	env->DeleteGlobalRef(g_bindingMusicSP.classObject);
}

std::shared_ptr<pa::Effect> pa::SoundPool::createNativeEffect(const pa::FilePath& path)
{
	auto effect = std::make_shared<pa::EffectSP>(path, g_bindingEffectSP);

	return effect;
}

std::shared_ptr<pa::Music> pa::SoundPool::createNativeMusic(const pa::FilePath& path)
{
	auto music = std::make_shared<pa::MusicSP>(path, g_bindingMusicSP);

	return music;
}