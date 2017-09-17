[%bs.raw {|require('./settings.css')|}];

let component = ReasonReact.statelessComponent "Settings";

let make ::isActive _children => {
  ...component,
  render: fun _self =>
    <div className=("settings" ^ (isActive == true ? " active" : ""))>
      <div> (ReasonReact.stringToElement "Settings") </div>
      <div> <button className="delete"> (ReasonReact.stringToElement "Delete") </button> </div>
    </div>
};
