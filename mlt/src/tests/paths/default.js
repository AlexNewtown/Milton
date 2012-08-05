{
   "scenefile" : {
      "version" : 0.1, 
      
      /**
       * Renderer
       */
      "renderer" : {
         "type" : "pathTracer", 
         "noRenderThreads" : 8, 
         "noDirectSamples" : 1, 
         
         "noSuperSamples"  : 16, 
         "generator" : "super", 
      }, 
      
      /**
       * Camera 
       */
      "camera" : {
         "type"  : "pinhole", 
         "eye"   : [ 3, .8, 0 ], 
         "up"    : [ 0, 1, 0 ], 
         "heightAngle" : 45, 
         "aspectRatio" : 1.0, 
         "near"  : 1, 
         "far"   : 100, 
      }, 
      
      /**
       * Scene (materials and shapes) 
       */
      "scene" : {
         "material": {
            "emitter" : {
               "type" : "oriented", 
               "power" : [ 15, 15, 15 ], 
            }, 
            
            "transform" : {
               "translate" : [ 1, 1, 0 ], 
               "transform" : {
                  "rotate" : [ 0, 0, 0, 0, 0, 1, 140 ], 
                  "scale"  : [ .75, 1, .75 ], 
                  "plane"  : { },
               }, 
            },
         }, 
         
         "material": {
            "bsdf" : {
               "type" : "diffuse", 
               "kd"   : [ .8, .1, .1 ], 
            }, 
            
            "transform" : {
               "scale"  : [ 10, 1, 10 ], 
               "plane"  : { },
            }, 
         }, 
         
         "material": {
            "bsdf" : {
               "type" : "phong", 
               "ks"   : [ .2, .8, .2 ], 
               "n"    : 10
            }, 
            
            "transform" : {
               "translate" : [ 0, .25, 1 ], 
               "transform" : {
                  "scale"  : [ .5, .5, .5 ], 
                  "sphere"  : { },
               }, 
            },
         }, 
         
         "material": {
            "bsdf" : {
               "type" : "specular", 
               "ks"   : .8, 
            }, 
            
            "transform" : {
               "translate" : [ 0, .25, 0 ], 
               "transform" : {
                  "scale"  : [ .5, .5, .5 ], 
                  "sphere"  : { },
               }, 
            },
         }, 

         "material": {
            "bsdf" : {
               "type" : "phong", 
               "ks"   : [ .1, .1, .5 ], 
               "n"    : 10
            }, 
            
            "transform" : {
               "translate" : [ 0, .25, -1 ], 
               "transform" : {
                  "scale"  : [ .5, .5, .5 ], 
                  "sphere"  : { },
               }, 
            },
         }, 
      }, 
   },
}

