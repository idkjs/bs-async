[@bs.send.pipe: Js.Promise.t('a)]
external map: ([@bs.uncurry] ('a => 'b)) => Js.Promise.t('b) = "then";
[@bs.send.pipe: Js.Promise.t('a)]
external recover':
  ([@bs.uncurry] (Js.Promise.error => 'a)) => Js.Promise.t('a) =
  "catch";
[@bs.send.pipe: Js.Promise.t('a)]
external map_recover':
  ([@bs.uncurry] ('a => 'b), [@bs.uncurry] (Js.Promise.error => 'b)) =>
  Js.Promise.t('b) =
  "then";
[@bs.send.pipe: Js.Promise.t('a)]
external then_catch':
  (
    [@bs.uncurry] ('a => Js.Promise.t('b)),
    [@bs.uncurry] (Js.Promise.error => Js.Promise.t('b))
  ) =>
  Js.Promise.t('b) =
  "then";

exception JSValue(Js.Types.tagged_t);

let is_exception: 'a => bool = (
  [%raw {|
  function (value) {
    return value instanceof Error;
  }
|}]:
    'a => bool
);

let error_to_exn = any =>
  if (Caml_exceptions.caml_is_extension(any)) {
    (Obj.magic(any): exn);
  } else if (is_exception(any)) {
    Caml_js_exceptions.Error(Obj.magic(any): Caml_js_exceptions.t);
  } else {
    JSValue(Js.Types.classify(any));
  };

let recover = (handler, promise) =>
  recover'(e => error_to_exn(e) |> handler, promise);

let catch = (handler, promise) =>
  Js.Promise.catch(e => error_to_exn(e) |> handler, promise);

let map_recover = (next, handler, promise) =>
  map_recover'(next, e => error_to_exn(e) |> handler, promise);

let then_catch = (next, handler, promise) =>
  then_catch'(next, e => error_to_exn(e) |> handler, promise);
