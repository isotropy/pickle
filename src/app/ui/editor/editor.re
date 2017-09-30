external require : list string => 'anything => unit = "window.require" [@@bs.val];

external getElementById : string => Dom.element = "document.getElementById" [@@bs.val];

type actions =
  | Edit string;

type state = {
  currentValue: string,
  editor: ref (option MonacoEditor.t)
};

let onDidChangeModelContent _event {ReasonReact.state: state, ReasonReact.reduce: reduce} =>
  reduce (fun _ => Edit state.editor.getValue);

let onEditorLoaded {ReasonReact.state: state} => {
  state.editor :=
    Some (
      MonacoEditor.create
        (getElementById "editor")
        {value: "<html>\n</html>", language: "javascript", theme: "vs-dark"}
    );
  state.editor.onDidChangeModelContent onDidChangeModelContent
};

let onMonacoLoaded () => require ["./vs/editor/editor.main"] onEditorLoaded;

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
  initialState: fun () => {currentValue: "", editor: ref None},
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
