/* Template will be the HTML doc into which the bundled script will be injected */
/* TODO */
let getTemplate script =>
  ReasonReact.cloneElement
    <div className="foo" /> props::{"data-payload": 1, "aria-label": "click me"} [||];
