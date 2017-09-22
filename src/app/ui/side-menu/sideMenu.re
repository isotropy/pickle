[%bs.raw {|require('./sideMenu.css')|}];

let component = ReasonReact.statelessComponent "SideMenu";

let make ::setActive _children => {
  let onFilesClicked _event => setActive 0;
  let onSettingsClicked _event => setActive 1;
  {
    ...component,
    render: fun _self =>
      <div className="side-menu">
        <div onClick=onFilesClicked> <img src="/files.svg" alt="Files" /> </div>
        <div onClick=onSettingsClicked> <img src="/settings.svg" alt="Settings" /> </div>
      </div>
  }
};
