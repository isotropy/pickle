[%bs.raw {|require('./settings.css')|}];

let component = ReasonReact.statelessComponent "Settings";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="settings">
      <div> (ReasonReact.stringToElement "Settings") </div>
      <div> <button className="delete"> (ReasonReact.stringToElement "Delete") </button> </div>
    </div>
};
