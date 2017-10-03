module SystemJS = {
  type t;
};

module SystemConfig = {
  type t;
  type plugins = {
    pluginBabel: string,
    systemjsBabelBuild: string
  };
  type extensions = {defaultExtension: string};
  /* type packages = {. / : Js.t {. defaultExtension : string } }; */
  /* TODO: packages with slash path? */
  type config = {
    map: plugins,
    transpiler: string
  };
  external setConfig : SystemJS.t => config => unit = "config" [@@bs.send];
  external import : SystemJS.t => string => unit = "" [@@bs.send];
};

external systemJS : SystemJS.t = "window.SystemJS" [@@bs.val];

let setConfig () =>
  SystemConfig.setConfig
    systemJS
    {
      map: {
        pluginBabel: "./plugins/plugin-babel.js",
        systemjsBabelBuild: "./plugins/systemjs-babel-browser.js"
      },
      transpiler: "pluginBabel"
    };

let onSystemJSLoaded () => setConfig ();

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

let getBundle entry => SystemConfig.import systemJS entry;
