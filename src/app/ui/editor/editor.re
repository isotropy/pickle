open MonacoEditor;

external require : array string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type action =
  | Edit string
  | UpdateModel monacoModel;

type state = {
  currentValue: string,
  editor: option MonacoEditor.t,
  models: option monacoModels
};

let edit value => Edit value;

let updateModel model => UpdateModel model;

let loadModels editor {ReasonReact.reduce: reduce, ReasonReact.state: state} =>
  List.iter
    (
      fun model => {
        let currentItem: Fs.file = model;
        let contents: Fs.contents = currentItem.contents;
        let path: string = currentItem.filename;
        let content =
          switch contents {
          | Fs.String string => string
          | Fs.List list => "nothing" /* TODO: To be handled for nested file structure */
          };
        let uri: MonacoEditor.uri = MonacoEditor.uri "file" "" path "";
        let editorModel = MonacoEditor.createModel content "typescript" uri;
        reduce updateModel editorModel
      }
    )
    Fs.fileSystem;

let onContentChange editor {ReasonReact.state: state, ReasonReact.reduce: reduce} changes => {
  let value = MonacoEditorInterface.getValue editor;
  reduce edit value
};

let onEditorLoaded self => {
  let options: MonacoEditor.options = {
    "language": "typescript",
    "value": "import Module1 from 'module1.js';",
    "theme": "vs-dark"
  };
  let editor = MonacoEditor.create (getElementById "editor") options;
  loadModels editor self;
  MonacoEditorInterface.onDidChangeModelContent editor (onContentChange editor self)
};

let loadMonacoEditor: (unit => unit) => unit = [%bs.raw
  {|
    function loadMonacoEditor(callback) {
      var loaderScript = document.createElement('script');
      loaderScript.type = 'text/javascript';
      loaderScript.src = './vs/loader.js';
      loaderScript.addEventListener('load', callback);
      document.body.appendChild(loaderScript);
    }
  |}
];

let component = ReasonReact.reducerComponent "Editor";

let make _children => {
  let onMonacoLoaded event self =>
    require [|"./vs/editor/editor.main"|] (fun () => onEditorLoaded self);
  {
    ...component,
    initialState: fun () => {currentValue: "", editor: None, models: None},
    didMount: fun self => {
      loadMonacoEditor (self.handle onMonacoLoaded);
      ReasonReact.NoUpdate
    },
    reducer: fun action state =>
      switch action {
      | Edit value => ReasonReact.Update {...state, currentValue: value}
      | UpdateModel model =>
        let id = model.id;
        /* let models = state.models;
           let newModels = [model, ...models]; */
        ReasonReact.Update {...state, currentValue: "test"}
      /* switch state.models {
         | id => ReasonReact.Update {...state, models: model}
         } */
      },
    render: fun _self => <div id="editor" className="editor" />
  }
};
