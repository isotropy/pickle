open MonacoEditor;

external require : array string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type actions =
  | Edit string;

type state = {
  currentValue: string,
  editor: option MonacoEditor.t
};

let onContentChange editor {ReasonReact.state: state, ReasonReact.reduce: reduce} => {
  let value = MonacoEditorInterface.getValue editor;
  reduce (fun value => Edit value)
};

let onEditorLoaded {ReasonReact.state: state, ReasonReact.reduce: reduce} => {
  let editor =
    MonacoEditor.create
      (getElementById "editor")
      {value: "<html>\n</html>", language: "javascript", theme: "vs-dark"};
  MonacoEditorInterface.onDidChangeModelContent editor (onContentChange editor)
};

let onMonacoLoaded () => require [|"./vs/editor/editor.main"|] onEditorLoaded;

let loadMonacoEditor: unit => unit = [%bs.raw
  {|
    function loadMonacoEditor() {
      var loaderScript = document.createElement('script');
      loaderScript.type = 'text/javascript';
      loaderScript.src = './vs/loader.js';
      loaderScript.addEventListener('load', onMonacoLoaded);
      document.body.appendChild(loaderScript);
    }
  |}
];

let component = ReasonReact.reducerComponent "Editor";

let make _children => {
  ...component,
  initialState: fun () => {currentValue: "", editor: None},
  didMount: fun _self => {
    loadMonacoEditor ();
    ReasonReact.NoUpdate
  },
  reducer: fun action state =>
    switch action {
    | Edit value => ReasonReact.Update {...state, currentValue: value}
    },
  render: fun _self => <div id="editor" className="editor" />
};
