[%bs.raw {|require('./app.css')|}];
[@bs.module] external logo : string = "./cucumber.png";

type action =
  | BumpCount
  | ToggleDialog(bool)
;

type state = { name: string, kudos: bool };

let component = ReasonReact.reducerComponent("App");
let make = (_children) => {
  ...component,
  initialState: () => { name: "bob", kudos: true },
  reducer: (action, state) =>
    switch (action) {
    | BumpCount => ReasonReact.Update({ ...state, name: "jim" })
    | ToggleDialog(_show) => ReasonReact.Update({ ...state, name: "jim" })
    },
  render: ({ state }) =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.stringToElement(state.name)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.stringToElement("To get started, edit"))
        <code> (ReasonReact.stringToElement(" src/app.re ")) </code>
        (ReasonReact.stringToElement("and save to reload."))
      </p>
    </div>
};