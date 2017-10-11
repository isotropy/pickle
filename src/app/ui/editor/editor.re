open MonacoEditor;

external require : array string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type action =
  | Edit string
  | SetEditor (option MonacoEditorInterface.t)
  | AddModel monacoModel
  | UpdateModel monacoModel;

/* | SetModel int; */
type retainedProps = {activeModel: int};

type state = {
  currentValue: string,
  editor: option MonacoEditorInterface.t,
  models: option monacoModels
  /* activeModel: int */
};

let edit value => Edit value;

let setEditor editor => SetEditor editor;

let addModel model => AddModel model;

let updateModel editorModel => UpdateModel editorModel;

/* let setModel modelId => SetModel modelId; */
let setEditorModel editor models activeModel => {
  let model: option monacoModel =
    switch models {
    | Some models =>
      Some (
        List.find
          (
            fun model => {
              Js.log model;
              model.path === activeModel
            }
          )
          models
      )
    | None => None
    };
  MonacoEditorInterface.setModel editor model
};

let initEditorModel editor model => setEditorModel editor model;

let loadModels editor {ReasonReact.reduce: reduce, ReasonReact.state: state} =>
  List.iter
    (
      fun model => {
        let currentItem: Fs.file = model;
        let modelId: int = currentItem.id;
        let contents: Fs.contents = currentItem.contents;
        let path: string = currentItem.filename;
        let content =
          switch contents {
          | Fs.String string => string
          | Fs.List list => "nothing" /* TODO: To be handled for nested file structure */
          };
        let uri: MonacoEditor.uri = MonacoEditor.uri "file" "" path "";
        let editorModel = MonacoEditor.createModel content "javascript" uri;
        /* if (modelId === 1) {
             /* To set first file on editor by default */
             reduce setModel 1
           }; */
        reduce addModel editorModel
      }
    )
    Fs.fileSystem;

let onContentChange editor {ReasonReact.state: state, ReasonReact.reduce: reduce} changes => {
  let value = MonacoEditorInterface.getValue editor;
  reduce edit value
};

let onEditorLoaded self => {
  let options: MonacoEditor.options = {"language": "javascript", "theme": "vs-dark"};
  let editor = MonacoEditor.create (getElementById "editor") options;
  self.ReasonReact.reduce setEditor editor;
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

let component = ReasonReact.reducerComponentWithRetainedProps "Editor";

let make ::activeModel _children => {
  let onMonacoLoaded event self =>
    require [|"./vs/editor/editor.main"|] (fun () => onEditorLoaded self);
  {
    ...component,
    initialState: fun () => {currentValue: "", editor: None, models: None},
    retainedProps: activeModel,
    didMount: fun self => {
      loadMonacoEditor (self.handle onMonacoLoaded);
      ReasonReact.NoUpdate
    },
    willReceiveProps: fun self => {
      if (self.retainedProps !== activeModel) {
        setEditorModel self.state.editor self.state.models activeModel
      };
      self.state
    },
    reducer: fun action state =>
      switch action {
      | Edit value => ReasonReact.Update {...state, currentValue: value}
      | SetEditor editor => ReasonReact.Update {...state, editor}
      /* | SetModel modelId =>
         ReasonReact.UpdateWithSideEffects
           {...state, activeModel: modelId}
           (fun {ReasonReact.state: state} => setEditorModel state.editor state.models modelId) */
      | AddModel model =>
        let newModels: monacoModels =
          switch state.models {
          | Some models => [model, ...models] /* TODO: Eliminate nesting */
          | None => [model]
          };
        ReasonReact.Update {...state, models: Some newModels}
      | UpdateModel model => ReasonReact.Update {...state, currentValue: "test"}
      },
    render: fun _self => <div id="editor" className="editor" />
  }
};
