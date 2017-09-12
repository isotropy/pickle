let component = ReasonReact.statelessComponent "Editor";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="editor">
    (ReasonReact.stringToElement "Editor")
    </div>
};
