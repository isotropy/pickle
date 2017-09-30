/* TODO: Replace interops */
/* external monaco : 'anything => unit = "window.monaco" [@@bs.val]; */
/* external require : 'anything => unit = "window.require" [@@bs.val]; */
type state = {currentValue: string};

type actions =
  | Edit string;

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

let onMonacoLoaded: unit => unit = [%bs.raw
  {|
        function onMonacoLoaded() {
          window.require(['./vs/editor/editor.main'], () => {
            let editor = monaco.editor.create(document.getElementById('editor'), {
              value: '<html>\n</html>',
              language: 'javascript',
              theme: 'vs-dark'
            });
            onEditorMount(editor);
          });
        }
    |}
];

let onEditorMount editor {ReasonReact.reduce: reduce} => {
  let onDidChangeModelContent _event => reduce (fun _ => Edit editor##getValue);
  ()
  /* editor##onDidChangeModelContent onDidChangeModelContent */
};

let component = ReasonReact.reducerComponent "Editor";

let make _children => {
  ...component,
  initialState: fun () => {currentValue: ""},
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
