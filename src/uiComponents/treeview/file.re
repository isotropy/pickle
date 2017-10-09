let component = ReasonReact.statelessComponent "File";

let make ::filename ::file ::setActiveFile _children => {
  let openFile _event => setActiveFile file;
  {
    ...component,
    render: fun self =>
      <div className="file" onClick=openFile>
        <div> (ReasonReact.stringToElement filename) </div>
      </div>
  }
};
