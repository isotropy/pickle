external monaco : 'anything => unit = "window.monaco" [@@bs.val];

type monacoModel = {id: int};

type monacoModels = list monacoModel;

module MonacoEditorInterface = {
  type t;
  external getValue : option t => string = "" [@@bs.send];
  external onDidChangeModelContent : option t => 'anything => unit = "" [@@bs.send];
};

module MonacoEditor = {
  type t;
  type options = Js.t {. value : string, language : string, theme : string};
  type uriScheme = string;
  type uriAuthority = string;
  type uriPath = string;
  type uriQuery = string;
  type uri = {
    scheme: uriScheme,
    authority: uriAuthority,
    path: uriPath,
    query: uriQuery
  };
  external uri : uriScheme => uriAuthority => uriPath => uriQuery => uri =
    "Uri" [@@bs.new] [@@bs.scope "monaco"];
  external createModel : string => string => uri => monacoModel =
    "" [@@bs.val "monaco.editor.createModel"];
  external create : Dom.element => options => option MonacoEditorInterface.t =
    "" [@@bs.val "monaco.editor.create"];
};
