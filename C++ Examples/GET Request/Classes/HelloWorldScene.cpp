#include "HelloWorldScene.h"

USING_NS_CC;

using namespace std;

// ANDROID requires
// <uses-permission android:name="android.permission.INTERNET"/>

// DON'T Forget to add "App Transport Security Settings" to Info.plist
// DON'T Forget to add "Allow Arbitrary Loads" under the previous section added inside of Info.plist and set it to YES

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest( );
    request->setUrl( "http://www.sonarlearning.co.uk/extras/cocostutorial/get.php" );
    request->setRequestType( cocos2d::network::HttpRequest::Type::GET );
    request->setResponseCallback( CC_CALLBACK_2( HelloWorld::onHttpRequestCompleted, this ) );
    cocos2d::network::HttpClient::getInstance()->send( request );
    request->release( );
    
    return true;
}

void HelloWorld::onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response )
{
    if ( 200 != response->getResponseCode( ) )
    {
        printf( "Succeeded" );
        return;
    }
    else
    {
        printf( "Failed" );
    }
}

