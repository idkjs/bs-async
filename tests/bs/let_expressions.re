let add = (a, b) => {
  let%async (x, y) = Js.Promise.resolve((a, b));
  x + y;
};

let add' = (a, b) => {
  let%async' (x, y) = Js.Promise.resolve((a, b));
  x + y |> Js.Promise.resolve;
};

let add_par = (a, b) => {
  let%async x = Js.Promise.resolve(a)
  and y = Js.Promise.resolve(b);
  x + y;
};

let add_par' = (a, b) => {
  let%async' x = Js.Promise.resolve(a)
  and y = Js.Promise.resolve(b);
  x + y |> Js.Promise.resolve;
};
