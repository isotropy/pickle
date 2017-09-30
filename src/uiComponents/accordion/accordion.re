type action =
  | Toggle;

type state = {accordionState: bool};

let component = ReasonReact.reducerComponent "Accordion";

let make ::title children => {
  ...component,
  initialState: fun () => {accordionState: false},
  reducer: fun action state =>
    switch action {
    | Toggle => ReasonReact.Update {...state, accordionState: not state.accordionState}
    },
  render: fun self =>
    <div className=("accordion " ^ (self.state.accordionState ? "expanded" : "collapsed"))>
      <h3 onClick=(self.reduce (fun _event => Toggle))> (ReasonReact.stringToElement title) </h3>
      <div> (ReasonReact.arrayToElement children) </div>
    </div>
};
