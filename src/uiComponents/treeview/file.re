let component = ReasonReact.statelessComponent "File";

let make ::filename ::file ::setActiveFile _children => {
  ...component,
  render: fun self =>
    <div className="file" onClick=(fun _ => setActiveFile ())>
      <div> (ReasonReact.stringToElement filename) </div>
    </div>
};
