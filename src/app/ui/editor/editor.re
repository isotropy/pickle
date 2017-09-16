open Bs_webapi.Dom;

let loadMonacoEditor: unit => unit = [%bs.raw
  {|
    function loadMonacoEditor() {
      var loaderScript = document.createElement('script');
      loaderScript.type = 'text/javascript';
      loaderScript.src = './vs/loader.js';

      var loaderMainScript = document.createElement('script');
      loaderMainScript.type = 'text/javascript';
      loaderMainScript.src = './vs/loader.js';
      loaderMainScript.addEventListener('load', onMonacoLoaded);
      document.body.appendChild(loaderScript);
      document.body.appendChild(loaderMainScript);
    }
  |}
];

/*
 let onMonacoLoaded: unit => unit = [%bs.raw
   {|
     function onMonacoLoaded() {
       this.editor = monaco.editor.create(document.getElementById('editor'), {
         value: '//Try loading a package below. Click on Save for transpiling.',
         language: 'javascript'
       });
     }
 |}
 ]; */
let onMonacoLoaded () => {
  /* editor: Js.Global.monaco.editor.create(Document.getElementById('editor'), {
       value: "//Try loading a package below. Click on Save for transpiling.",
       language: 'javascript'
     }); */
};

type state = {currentValue: string};

type actions =
  | Edit;

let component = ReasonReact.reducerComponent "Editor";

let make _children => {
  ...component,
  initialState: fun () => {currentValue: ""},
  didMount: fun self => {
    loadMonacoEditor ();
    ReasonReact.NoUpdate
  },
  reducer: fun action state =>
    switch action {
    | Edit => ReasonReact.Update {...state, currentValue: "nothing"}
    },
  render: fun {state, reduce} =>
    <div id="editor" className="editor" onClick=(reduce (fun _ => Edit))>
      (ReasonReact.stringToElement "Editor")
    </div>
};
