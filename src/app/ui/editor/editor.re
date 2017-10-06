open MonacoEditor;

external require : array string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type action =
  | Edit string;

type state = {
  currentValue: string,
  editor: option MonacoEditor.t
};

let onContentChange editor {ReasonReact.state: state, ReasonReact.reduce: reduce} changes => {
  let value = MonacoEditorInterface.getValue editor;
  reduce (fun value => Edit value) /* TODO: How do we access self.ReasonReact.reduce here? */
};

let onEditorLoaded self => {
  let options: MonacoEditor.options = {
    "value": "<html>\n</html>",
    "language": "javascript",
    "theme": "vs-dark"
  };
  let editor = MonacoEditor.create (getElementById "editor") options;
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

let edit value => Edit value;

let make _children => {
  let onMonacoLoaded event self =>
    require
      [|"./vs/editor/editor.main"|]
      onEditorLoaded; /* TODO: Can self be passed to this callback? Call/Apply? */
  {
    ...component,
    initialState: fun () => {currentValue: "", editor: None},
    didMount: fun self => {
      loadMonacoEditor (self.handle onMonacoLoaded);
      ReasonReact.NoUpdate
    },
    reducer: fun action state =>
      switch action {
      | Edit value => ReasonReact.Update {...state, currentValue: value}
      },
    render: fun _self => <div id="editor" className="editor" />
  }
};
