#! /usr/bin/octave -q

AZ = 26;
ai = uint8('A') - 1;
t = input('');
for ti = 1:t
	n = input('');
	%arr = 1:n;
	arr = {};
	for i = 1:n
		%arr(i) = input('')
		s= input('', 's');
		arr(end+1)=s;
	end
	
	GT = zeros(AZ, AZ);

	hasAns = true;

	for i = 1:(n-1)
		a = cell2mat(arr(i));
		b = cell2mat(arr(i+1));
		ok = false;
		for j = 1:(size(a,2))
			if j > size(b,2)
				break;
			end
			
			if a(j) ~= b(j)
				x = uint8(a(j)) - ai;
				y = uint8(b(j)) - ai;
				GT(y,x) = 1;
				ok = true;
				break;
			end
		end
		if ~ok && size(a,2) > size(b,2)
			hasAns = false;
			break;
		end
	end
	
	if hasAns
		res = zeros(AZ,1);
		done = zeros(AZ,1);

		for i = 1:AZ
			best = -1;
			for j = 1:AZ
				if done(j)
					continue;
				end
				bad = max(GT(j,:));
				if bad == 0
					best = j;
					break
				end
			end

			if best == -1
				hasAns = false;
				break;
			end

			GT(:, best) = 0;
			res(best) = i;
			done(best) = true;
		end

		if hasAns
			for i = 1:n
				a = cell2mat(arr(i));
				for j = 1:size(a,2)
					a(j) = char(res(uint8(a(j)) - ai) + ai);
				end
				fprintf('%s\n', a);
			end
		end
	end

	if ~hasAns
		fprintf('#\n'); 
	end
end