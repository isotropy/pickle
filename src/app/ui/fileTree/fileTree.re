[%bs.raw {|require('./fileTree.css')|}];

let component = ReasonReact.statelessComponent "FileTree";

let make ::isActive ::setActiveFile _children => {
  ...component,
  render: fun {state, reduce} => {
    let fs = Fs.fileSystem;
    let fsItems =
      List.map
        (
          fun fsItem => {
            let currentItem: Fs.file = fsItem;
            let fileName: string = currentItem.filename;
            let contents: Fs.contents = fsItem.contents;
            switch contents {
            | Fs.String string =>
              <File
                filename=fileName
                file=currentItem
                setActiveFile=(fun _ => setActiveFile fileName)
              />
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
