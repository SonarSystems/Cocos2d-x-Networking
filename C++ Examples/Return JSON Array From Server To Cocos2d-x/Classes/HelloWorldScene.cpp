#include "HelloWorldScene.h"
#include <vector>
#include "spine/Json.h"

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
    request->setUrl( "http://www.sonarlearning.co.uk/extras/cocostutorial/jsonarray.php" );
    request->setRequestType( cocos2d::network::HttpRequest::Type::GET );
    request->setResponseCallback( CC_CALLBACK_2( HelloWorld::onHttpRequestCompleted, this ) );
    cocos2d::network::HttpClient::getInstance()->send( request );
    request->release();
    
    return true;
}

void HelloWorld::onHttpRequestCompleted( cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response )
{
    // The data will be placed in the buffer.
    std::vector<char> * buffer = response->getResponseData( );
    char *concatenated = ( char * ) malloc( buffer->size( ) + 1 );
    std::string s2( buffer->begin( ), buffer->end( ) );
    strcpy( concatenated, s2.c_str( ) );
    
    // JSON Parser
    Json *json = Json_create( concatenated );
    int test1 = Json_getInt( json, "a", -1 );
    const char *test2 = Json_getString( json, "b", "default" );
    float test3 = Json_getFloat( json, "c", -1.0f );
    
    // View the console
    log( "HTTP Response : key a : %i", test1 );
    log( "HTTP Response : key b : %s", test2 );
    log( "HTTP Response : key c : %f", test3 );
    
    // Delete the JSON object
    Json_dispose( json );
    
    
    if ( response->getResponseCode( ) == 200 )
    {
        printf( "Succeeded" );
        return;
    }
    else
    {
        printf("Failed");
    }
}

