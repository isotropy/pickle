[%bs.raw {|require('./fileTree.css')|}];

type state = {fs: Fs.fileSystem};

let component = ReasonReact.reducerComponent "FileTree";

let make ::isActive ::setActiveFile _children => {
  ...component,
  initialState: fun () => {
    fs: Fs.fileSystem,
    activeFile: {id: 0, dir: "", filename: "", contents: Fs.String ""}
  },
  reducer: fun action state =>
    switch action {
    | SetActiveFile file =>
      ReasonReact.UpdateWithSideEffects
        {...state, activeFile: file}
        (fun {ReasonReact.reduce: reduce} => reduce Editor.setModel activeFileId)
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
            | Fs.String string => <File filename=fileName file=currentItem setActiveFile />
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
