type state = {script: string};

let component = ReasonReact.statefulComponent "Preview";

let make _children => {
  ...component,
  initialState: fun () => {script: ""},
  didMount: fun {state} => {
    let bundle = Build.getBundle ();
    let script = ReactDOMServerRe.renderToString (Template.getTemplate bundle);
    ReasonReact.Update {...state, script}
  },
  render: fun _self =>
    <div className="preview"> <iframe width="100%" height="100%" src="" /> </div>
};
