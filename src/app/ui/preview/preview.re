let component = ReasonReact.statefulComponent "Preview";

let make _children => {
  let renderFrame _event =>
    ReactDOMServerRe.renderToString (Template.getTemplate self.state.script);
  {
    ...component,
    initialState: fun () => {script: ""},
    render: fun _self =>
      <div className="preview">
        <iframe width="100%" height="100%" src=(self.handle renderFrame) />
      </div>
  }
};
