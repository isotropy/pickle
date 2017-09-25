[%bs.raw {|require('./sideMenu.css')|}];

let component = ReasonReact.statelessComponent "SideMenu";

let make ::setActive _children => {
  let onFilesClicked _event => setActive 0;
  let onSettingsClicked _event => setActive 1;
  {
    ...component,
    render: fun _self =>
      <div className="side-menu">
        <div className="files" onClick=onFilesClicked />
        <div className="settings" onClick=onSettingsClicked />
      </div>
  }
};
