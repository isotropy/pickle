[%bs.raw {|require('./fileTree.css')|}];

let component = ReasonReact.statelessComponent "FileTree";

let make ::isActive _children => {
  ...component,
  render: fun _self =>
    <div className=("file-tree" ^ (isActive == true ? " active" : ""))>
      (ReasonReact.stringToElement "File View")
    </div>
};
