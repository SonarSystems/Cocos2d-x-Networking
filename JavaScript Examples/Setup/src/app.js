// ANDROID requires
// <uses-permission android:name="android.permission.INTERNET"/>

// DON'T Forget to add "App Transport Security Settings" to Info.plist
// DON'T Forget to add "Allow Arbitrary Loads" under the previous section added inside of Info.plist and set it to YES

var HelloWorldLayer = cc.Layer.extend({
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();
    
        var xhr = cc.loader.getXMLHttpRequest();
        
        xhr.open( "METHOD", "Enter URL HERE" );
        xhr.setRequestHeader( "Content-Type", "text/plain" );
                                      
        xhr.onreadystatechange = function ()
        {
            if ( xhr.readyState == 4 && ( xhr.status >= 200 && xhr.status <= 207 ) )
            {
                var httpStatus = xhr.statusText;
                cc.log( httpStatus );
            }
        }
                                      
        return true;
    },
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

