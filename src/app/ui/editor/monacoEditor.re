type t;

type editorInit = {
  value: string,
  language: string,
  theme: string
};

external monaco : 'anything => unit = "window.monaco" [@@bs.val];

external create : Dom.element => editorInit => t = "" [@@bs.scope "editor"] [@@bs.val "monaco"];

external onDidChangeModelContent : t => unit = "" [@@bs.val];

external getValue : t => string = "" [@@bs.get];
