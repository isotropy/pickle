[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent "App";

let make _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "Pickle") </h2>
      </div>
      <div className="columns">
        <SideMenu />
        <FileTree />
        <Editor />
      </div>
    </div>
};
