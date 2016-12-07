open Printf
open Scanf
open Array

external id : 'a -> 'a = "%identity"

let rec solve t =
    match t with
    | [] -> (0,1000000000)
    | hd :: tl ->
        let (f0, f1) = solve tl in
        (f1, hd + min f0 f1)

let () =
  let t = scanf " %d" id in
  for i = 1 to t do
    let n = scanf " %d" id in
    let t = Array.init n (fun _ -> scanf " %d" id) in
    let (f0,f1) = solve (to_list t) in
    
    printf "%d\n" f1
  done
