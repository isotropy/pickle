let component = ReasonReact.statelessComponent "File";

let make ::filename ::file _children => {
  let openFile _event => Js.log file;
  {
    ...component,
    render: fun _self =>
      <div className="file" onClick=openFile>
        <div> (ReasonReact.stringToElement filename) </div>
        <div> (ReasonReact.stringToElement "File") </div>
      </div>
  }
};
