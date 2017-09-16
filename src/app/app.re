[%bs.raw {|require('./app.css')|}];

type action =
  | SetActivePanel activePanel;

type state = {activePanel: int};

let setActivePanel activePanel => SetActivePanel activePanel;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {activePanel: 0},
  reducer: fun action state =>
    switch action {
    | SetActivePanel panelNo => ReasonReact.Update {...state, activePanel: panelNo}
    },
  render: fun {state, reduce} =>
    <div className="App">
      <div className="App-header"> <h2> (ReasonReact.stringToElement "Pickle") </h2> </div>
      <div className="columns">
        <SideMenu setActive=(reduce (setActivePanel activePanel)) />
        <Settings />
        <FileTree />
        <Editor />
      </div>
    </div>
};
