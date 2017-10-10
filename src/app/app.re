[%bs.raw {|require('./app.css')|}];

type action =
  | SetActivePanel int
  | SetActiveFile Fs.file;

type state = {
  activePanel: int,
  activeFile: int
};

let setActiveFile activeFileId => SetActiveFile activeFileId;

let setActivePanel activePanel => SetActivePanel activePanel;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {activePanel: 0, activeFile: 1},
  didMount: fun state => {
    Build.loadSystemJS ();
    ReasonReact.NoUpdate
  },
  reducer: fun action state =>
    switch action {
    | SetActivePanel panelNo => ReasonReact.Update {...state, activePanel: panelNo}
    | SetActiveFile fileId => ReasonReact.Update {...state, activeFile: fileId}
    },
  render: fun {state, reduce} =>
    <div className="App">
      <div className="App-header"> <h2> (ReasonReact.stringToElement "Pickle") </h2> </div>
      <div className="columns">
        <SideMenu setActive=(reduce setActivePanel) />
        <FileTree isActive=(state.activePanel == 0) setActiveFile=(reduce setActiveFile) />
        <Settings isActive=(state.activePanel == 1) />
        <Editor activeModel=state.activeFile />
        <Preview />
      </div>
    </div>
};
