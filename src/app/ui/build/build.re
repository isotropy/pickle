type bundle = string;

external systemJS : 'anything => unit = "window.SystemJS" [@@bs.val];

let loadSystemJS: unit => unit = [%bs.raw
  {|
     function loadSystemJS() {
       var loaderScript = document.createElement('script');
       loaderScript.type = 'text/javascript';
       loaderScript.src = './systemjs/system.js';
       loaderScript.addEventListener('load', onSystemJSLoaded);
       document.body.appendChild(loaderScript);
     }
   |}
];

let onSystemJSLoaded: unit => unit = [%bs.raw
  {|
  function onSystemJSLoaded() {
    let systemJSConfig = SystemJS.config;
    setConfig(systemJSConfig);
  }
  |}
];

let setConfig config =>
  config {
    "map": {
      "resolve": "/plugin-resolve/plugin-resolve.js",
      "plugin-babel": "/plugin-babel/plugin-babel.js",
      "systemjs-babel-build": "/plugin-babel/systemjs-babel-browser.js"
    },
    "packages": {"/": {defaultExtension: "js"}},
    "transpiler": "plugin-babel"
  };

let getBundle entry => Js.log entry;
