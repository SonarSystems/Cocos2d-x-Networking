#include "HelloWorldScene.h"
#include <vector>

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
    request->setUrl( "http://www.sonarlearning.co.uk/extras/cocostutorial/post.php" );
    request->setRequestType( cocos2d::network::HttpRequest::Type::POST );
    request->setResponseCallback( CC_CALLBACK_2( HelloWorld::onHttpRequestCompleted, this ) );
    request->setRequestData( "dataOne=45", 10 );
    cocos2d::network::HttpClient::getInstance()->send( request );
    request->release( );
    
    return true;
}

void HelloWorld::onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response )
{
    std::vector<char> *buffer = response->getResponseData( );
    
    printf( "Get data: ");
    for ( unsigned int i = 0; i < buffer->size( ); i++ )
    {
        printf( "%c", ( *buffer )[i] );
    }
    printf( "\n" );
    
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

