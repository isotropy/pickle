let component = ReasonReact.statelessComponent "SideMenu";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="side-menu">
      (ReasonReact.stringToElement "Side Menu")
    </div>
};
