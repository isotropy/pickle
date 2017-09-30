[%bs.raw {|require('./fileTree.css')|}];

type action =
  | SetActiveFile Fs.file;

let setActiveFile activeFile => SetActiveFile activeFile;

type state = {
  fs: Fs.fileSystem,
  activeFile: Fs.file
};

let component = ReasonReact.reducerComponent "FileTree";

let make ::isActive _children => {
  ...component,
  initialState: fun () => {
    fs: Fs.fileSystem,
    activeFile: {dir: "", filename: "", contents: Fs.String ""}
  },
  reducer: fun action state =>
    switch action {
    | SetActiveFile file => ReasonReact.Update {...state, activeFile: file}
    },
  render: fun {state} => {
    let {fs} = state;
    let fsItems =
      List.map
        (
          fun fsItem => {
            let currentItem: Fs.file = fsItem;
            let contents: Fs.contents = fsItem.contents;
            switch contents {
            | Fs.String string => <File filename=string file=currentItem />
            | Fs.List list => <Directory />
            }
          }
        )
        fs;
    let view =
      List.length fsItems === 0 ?
        ReasonReact.nullElement : ReasonReact.arrayToElement (Array.of_list fsItems);
    <div className=("file-tree" ^ (isActive == true ? " active" : ""))> view </div>
  }
};
