let component = ReasonReact.statelessComponent "Directory";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="directory"> <div> (ReasonReact.stringToElement "Directory") </div> </div>
};
