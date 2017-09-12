let component = ReasonReact.statelessComponent "FileTree";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="file-tree">
      (ReasonReact.stringToElement "File View")
    </div>
};
