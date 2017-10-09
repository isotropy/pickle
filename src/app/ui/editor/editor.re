open MonacoEditor;

external require : array string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type action =
  | Edit string
  | AddModel monacoModel
  | UpdateModel monacoModel
  | SetModel int;

type state = {
  currentValue: string,
  editor: option MonacoEditor.t,
  models: option monacoModels,
  activeModel: int
};

let edit value => Edit value;

let addModel model => AddModel model;

let updateModel editorModel => UpdateModel editorModel;

let setModel modelId => SetModel modelId;

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
        reduce addModel editorModel
      }
    )
    Fs.fileSystem;

let initEditorModel editor state => {
  /* TODO: Access State?! */
  let model =
    switch state.models {
    | Some models => Js.log models
    /* List.find models.id === 1 */
    | None => Js.log "none"
    };
  ()
  /* setEditorModel editor model */
};

let onContentChange editor {ReasonReact.state: state, ReasonReact.reduce: reduce} changes => {
  let value = MonacoEditorInterface.getValue editor;
  initEditorModel editor state;
  reduce edit value
};

let setEditorModel editor model => MonacoEditorInterface.setModel editor model;

let onEditorLoaded self => {
  let options: MonacoEditor.options = {"language": "javascript", "theme": "vs-dark"};
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
    initialState: fun () => {currentValue: "", editor: None, models: None, activeModel: 1},
    didMount: fun self => {
      loadMonacoEditor (self.handle onMonacoLoaded);
      ReasonReact.NoUpdate
    },
    reducer: fun action state =>
      switch action {
      | Edit value => ReasonReact.Update {...state, currentValue: value}
      | SetModel modelId => ReasonReact.Update {...state, activeModel: modelId}
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
