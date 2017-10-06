external monaco : 'anything => unit = "window.monaco" [@@bs.val];

module MonacoEditorInterface = {
  type t;
  external getValue : option t => string = "" [@@bs.send];
  external onDidChangeModelContent : option t => 'anything => unit = "" [@@bs.send];
};

module MonacoEditor = {
  type t;
  type options = Js.t {. value : string, language : string, theme : string};
  external create : Dom.element => options => option MonacoEditorInterface.t =
    "" [@@bs.val "monaco.editor.create"];
};
