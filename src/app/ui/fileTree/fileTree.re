[%bs.raw {|require('./fileTree.css')|}];

type action =
  | SetActiveFile Fs.file;

let setActiveFile activeFile => {
  let file: Fs.file = activeFile;
  let activeFileId: int = activeFile.id;
  Editor.setModel activeFileId;
  SetActiveFile activeFile
};

type state = {
  fs: Fs.fileSystem,
  activeFile: Fs.file
};

let component = ReasonReact.reducerComponent "FileTree";

let make ::isActive _children => {
  ...component,
  initialState: fun () => {
    fs: Fs.fileSystem,
    activeFile: {id: 0, dir: "", filename: "", contents: Fs.String ""}
  },
  reducer: fun action state =>
    switch action {
    | SetActiveFile file => ReasonReact.Update {...state, activeFile: file}
    },
  render: fun {state, reduce} => {
    let {fs} = state;
    let fsItems =
      List.map
        (
          fun fsItem => {
            let currentItem: Fs.file = fsItem;
            let fileName: string = currentItem.filename;
            let contents: Fs.contents = fsItem.contents;
            switch contents {
            | Fs.String string =>
              <File filename=fileName file=currentItem setActiveFile=(reduce setActiveFile) />
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
