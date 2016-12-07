const
MAXN=1111;

var
ntest,test: int64;
g: array [1..MAXN, 1..MAXN] of boolean;
i,j,k:int64;
n,m:int64;
a,b:int64;
color: array[1..MAXN] of int64;
res: int64;
start: int64;
seen: array[1..MAXN] of boolean;
// stack
st: array[1..MAXN] of int64;
si: int64;
// component
size, most: int64;
counts: array[1..MAXN] of int64;

procedure push(x: int64);
begin
    si:=si+1;
    st[si] := x;
end;

function pop:integer;
begin
    si:=si-1;
    pop := st[si+1];
end;

begin
    read(ntest);
    for test:=1 to ntest do begin
        for i := 1 to MAXN do begin
            seen[i] := false;
            for j := 1 to MAXN do begin
                g[i,j] := false;
            end;
        end;

        read(n,m);

        for i := 1 to m do begin
            read(a,b);
            g[a,b] := true; g[b,a] := true;
        end;
        for i := 1 to n do read(color[i]);

        res := 0; si := 0;

        for start := 1 to n do begin
            if seen[start] then continue;
            for i := 1 to MAXN do counts[i] := 0;
            size := 0; most := 0;
            si := 0;
            push(start);
            seen[start] := true;
            repeat
                a := pop;
                size := size + 1;
                counts[color[a]] := counts[color[a]] + 1;
                if counts[color[a]] > most then most := counts[color[a]];

                for b := 1 to n do begin
                    if seen[b] or not g[a,b] then continue;
                    seen[b] := true;
                    push(b);
                end;
            until si = 0;

            res := res + (size - most);
        end;
        writeln(res);
    end;
end.