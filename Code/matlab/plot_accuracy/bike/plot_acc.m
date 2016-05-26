function  plot_acc(file_name,file_name1,color, color1)
accury = load(file_name);
accury = cumsum(accury);
[m,n] = size(accury);
accury =accury/(accury(m*n));
accury(m*n)= accury(m*n - 1);

accury1 = load(file_name1);
accury1 = cumsum(accury1);
[m,n] = size(accury1);
accury1 =accury1/(accury1(m*n));
accury1(m*n)= accury1(m*n - 1);

set(0,'defaultaxesfontsize',24);
set(0,'defaultaxesfontname','Tahoma');
set(0,'defaultaxesfontweight','bold');
X=[0 0.00125 0.0025 0.00375 0.005 0.00625 0.0075 0.00875 0.01 0.01125 0.0125 0.01375 0.015 0.01625 0.0175 0.01875 0.02 0.02125 0.0225 0.02375 0.025 0.02625 0.0275 0.02875 0.03 0.03125 0.0325 0.03375 0.035 0.03625 0.0375 0.03875 0.04 0.04125 0.0425 0.04375 0.045 0.04625 0.0475 0.04875 0.05 0.05125 0.0525 0.05375 0.055 0.05625 0.0575 0.05875 0.06 0.06125 0.0625 0.06375 0.065 0.06625 0.0675 0.06875 0.07 0.07125 0.0725 0.07375 0.075 0.07625 0.0775 0.07875 0.08 0.08125 0.0825 0.08375 0.085 0.08625 0.0875 0.08875 0.09 0.09125 0.0925 0.09375 0.095 0.09625 0.0975 0.09875 0.1 0.10125 0.1025 0.10375 0.105 0.10625 0.1075 0.10875 0.11 0.11125 0.1125 0.11375 0.115 0.11625 0.1175 0.11875 0.12 0.12125 0.1225 0.12375 0.125 0.12625 0.1275 0.12875 0.13 0.13125 0.1325 0.13375 0.135 0.13625 0.1375 0.13875 0.14 0.14125 0.1425 0.14375 0.145 0.14625 0.1475 0.14875 0.15 0.15125 0.1525 0.15375 0.155 0.15625 0.1575 0.15875 0.16 0.16125 0.1625 0.16375 0.165 0.16625 0.1675 0.16875 0.17 0.17125 0.1725 0.17375 0.175 0.17625 0.1775 0.17875 0.18 0.18125 0.1825 0.18375 0.185 0.18625 0.1875 0.18875 0.19 0.19125 0.1925 0.19375 0.195 0.19625 0.1975 0.19875 0.2 0.20125 0.2025 0.20375 0.205 0.20625 0.2075 0.20875 0.21 0.21125 0.2125 0.21375 0.215 0.21625 0.2175 0.21875 0.22 0.22125 0.2225 0.22375 0.225 0.22625 0.2275 0.22875 0.23 0.23125 0.2325 0.23375 0.235 0.23625 0.2375 0.23875 0.24 0.24125 0.2425 0.24375 0.245 0.24625 0.2475 0.24875 ];
Yfinal = [0.00144906 0.00569166 0.0116821 0.020496 0.0287272 0.0430983 0.0567523 0.0708694 0.0807141 0.0942336 0.104467 0.117523 0.127383 0.13784 0.147102 0.159128 0.170705 0.180341 0.192755 0.203062 0.213848 0.224813 0.236451 0.247714 0.258127 0.266582 0.278847 0.289304 0.302256 0.312339 0.32187 0.33173 0.341336 0.352256 0.361324 0.370376 0.381356 0.390783 0.398192 0.410039 0.418957 0.42683 0.436809 0.442979 0.449761 0.456991 0.463878 0.47081 0.479803 0.485823 0.491575 0.49885 0.506498 0.512593 0.518061 0.52314 0.527263 0.532133 0.537451 0.542874 0.549029 0.553989 0.557559 0.563206 0.56709 0.57202 0.576367 0.581745 0.586495 0.590768 0.59386 0.596504 0.602256 0.605244 0.609098 0.613549 0.617523 0.620571 0.624036 0.628862 0.632327 0.636017 0.638408 0.64026 0.64383 0.646952 0.64988 0.652584 0.654004 0.656005 0.658635 0.660875 0.663878 0.666059 0.667986 0.669376 0.671646 0.673872 0.676277 0.677891 0.679668 0.68182 0.684001 0.685793 0.688198 0.689842 0.692038 0.694174 0.695787 0.697356 0.698745 0.700329 0.701479 0.702883 0.704601 0.705542 0.706558 0.708545 0.710099 0.711697 0.712758 0.714565 0.715895 0.717583 0.718405 0.719615 0.720944 0.722259 0.72305 0.725007 0.726352 0.727398 0.728727 0.729444 0.730281 0.731237 0.732148 0.733717 0.734613 0.735524 0.736182 0.737631 0.738467 0.739005 0.739886 0.740589 0.741948 0.742994 0.74386 0.74513 0.74625 0.747431 0.748342 0.749641 0.750433 0.751165 0.751808 0.752644 0.753257 0.754033 0.754631 0.755423 0.756259 0.756707 0.75729 0.757738 0.758754 0.759396 0.759845 0.760756 0.761817 0.762653 0.763191 0.763968 0.764371 0.764969 0.765477 0.766194 0.766433 0.766926 0.767314 0.767658 0.768091 0.768748 0.769166 0.769779 0.770063 0.770601 0.770914 0.771123 0.771452 0.7719 0.772109 0.772722 0.772931 0.773424 0.773887 0.774186 0.775067 0.775381 ];
Yinit = [0.000971019 0.00162832 0.00457126 0.00872423 0.0123394 0.0170451 0.0214969 0.0267702 0.0307738 0.0352256 0.0389603 0.0447864 0.0490589 0.0524798 0.0554377 0.0589035 0.063176 0.0668061 0.0714969 0.0761876 0.0798327 0.0842844 0.0886764 0.0934568 0.0980131 0.102226 0.106394 0.109247 0.113355 0.117374 0.120362 0.124335 0.128712 0.13282 0.13651 0.139588 0.143412 0.14752 0.151628 0.155856 0.159695 0.163983 0.167747 0.17084 0.174395 0.177457 0.181043 0.184299 0.18781 0.190708 0.194129 0.196908 0.199044 0.201867 0.205094 0.20726 0.209247 0.212011 0.214924 0.217971 0.220317 0.222782 0.22553 0.22813 0.230102 0.232148 0.23412 0.237362 0.239603 0.241515 0.243845 0.246116 0.249074 0.250911 0.253152 0.255736 0.257604 0.259576 0.262145 0.263893 0.266044 0.268778 0.270063 0.271721 0.272692 0.274574 0.276666 0.279026 0.280983 0.282955 0.284807 0.286555 0.288467 0.29014 0.291634 0.293487 0.295817 0.297236 0.299134 0.300284 0.302002 0.304377 0.306005 0.30723 0.30856 0.30983 0.311548 0.313086 0.315133 0.316731 0.317747 0.319495 0.320989 0.322214 0.323663 0.325082 0.326591 0.32801 0.329773 0.331312 0.332566 0.333747 0.33527 0.336436 0.337855 0.339125 0.341171 0.342605 0.34398 0.345414 0.346908 0.347983 0.35 0.351479 0.352853 0.354287 0.355512 0.35735 0.358903 0.360726 0.362011 0.36334 0.365447 0.366716 0.367837 0.369525 0.370825 0.372692 0.374305 0.375769 0.377353 0.37922 0.381058 0.382552 0.383687 0.385285 0.386361 0.388004 0.389393 0.391888 0.392979 0.394129 0.395264 0.396699 0.398222 0.399761 0.401643 0.403167 0.404586 0.405707 0.40723 0.409068 0.410054 0.411563 0.412578 0.413848 0.415178 0.416567 0.417956 0.41942 0.420556 0.422259 0.423424 0.424604 0.425889 0.42683 0.428234 0.42919 0.429848 0.430908 0.432208 0.433358 0.434598 0.435704 0.436973 0.438527 0.439513 0.440887 0.44277 0.44401 ];
Ygtfinal = [0.000627428 0.002928 0.0076337 0.0132507 0.0189722 0.0261129 0.0339707 0.0410666 0.0471168 0.0560502 0.0631013 0.0710935 0.0794592 0.0859426 0.0918733 0.098282 0.105647 0.112474 0.11963 0.126696 0.133777 0.140544 0.147774 0.155796 0.162817 0.170122 0.175605 0.181401 0.188497 0.195025 0.200687 0.20599 0.213579 0.219376 0.22571 0.231386 0.236944 0.242486 0.247625 0.253929 0.25977 0.264819 0.270003 0.273364 0.276188 0.280206 0.283597 0.288109 0.293322 0.296489 0.300433 0.30354 0.307006 0.310532 0.313759 0.316911 0.31954 0.321975 0.324694 0.327831 0.331162 0.333806 0.335883 0.338632 0.340783 0.343591 0.345817 0.348626 0.351195 0.353466 0.355557 0.357171 0.360278 0.361697 0.3647 0.366702 0.369181 0.370795 0.372811 0.374813 0.37689 0.378638 0.379833 0.381162 0.383313 0.3853 0.386495 0.387676 0.388422 0.389752 0.391545 0.393218 0.395593 0.396923 0.398252 0.399328 0.400717 0.401942 0.403376 0.404377 0.405931 0.407484 0.408485 0.409994 0.411055 0.411861 0.413146 0.41452 0.416313 0.417329 0.418375 0.419435 0.420197 0.421049 0.422348 0.423185 0.424051 0.425202 0.426262 0.427711 0.428279 0.429131 0.429788 0.43061 0.431207 0.431745 0.432626 0.433911 0.434613 0.435987 0.437093 0.437929 0.439125 0.439662 0.440574 0.441455 0.442008 0.442979 0.443771 0.444338 0.44519 0.446116 0.447132 0.447849 0.44888 0.449641 0.450359 0.450777 0.451643 0.452644 0.45369 0.454332 0.454945 0.455677 0.45608 0.456917 0.457439 0.458754 0.459232 0.45971 0.460263 0.460846 0.461488 0.462205 0.462982 0.463385 0.463968 0.46461 0.465073 0.46579 0.466448 0.467135 0.467523 0.468016 0.468614 0.469361 0.469943 0.470317 0.470615 0.471512 0.471796 0.472483 0.473394 0.473812 0.474754 0.475545 0.475964 0.476621 0.47683 0.477891 0.478548 0.47925 0.479549 0.480639 0.481058 0.481715 0.482357 0.482776 0.483403 0.483941 ];
Yfuzzy = [ 0.00155824 0.00427017 0.00552875 0.0094693 0.0186689 0.0277187 0.037173 0.0425669 0.0485901 0.0560517 0.06191 0.0671241 0.0705403 0.0736268 0.0799047 0.089389 0.0967906 0.100117 0.10602 0.111579 0.117153 0.124389 0.135327 0.141755 0.149441 0.160708 0.169803 0.177265 0.187678 0.195994 0.200443 0.20801 0.216221 0.223038 0.228791 0.233991 0.241377 0.247101 0.257978 0.264107 0.275104 0.282311 0.288334 0.297324 0.303392 0.312577 0.31818 0.32702 0.333553 0.339756 0.349495 0.355368 0.363834 0.37125 0.377603 0.384061 0.389215 0.395388 0.401471 0.408184 0.414776 0.419646 0.426733 0.430494 0.437026 0.44251 0.448563 0.452609 0.458871 0.465749 0.469494 0.471757 0.477465 0.481091 0.486905 0.492988 0.497183 0.501558 0.506278 0.509814 0.515537 0.521875 0.524138 0.530161 0.537278 0.541638 0.546987 0.551991 0.556396 0.56188 0.56597 0.57099 0.573537 0.576444 0.578302 0.583411 0.587501 0.592041 0.597465 0.600072 0.603188 0.60602 0.609137 0.611759 0.616898 0.620299 0.622741 0.625888 0.628645 0.632166 0.634668 0.637245 0.641066 0.644047 0.646055 0.648437 0.651119 0.653142 0.656708 0.660364 0.662087 0.664439 0.669354 0.671616 0.674298 0.676755 0.678823 0.682644 0.684681 0.688697 0.69039 0.693327 0.69499 0.698376 0.702976 0.705508 0.707096 0.709883 0.713539 0.715157 0.71721 0.719127 0.720791 0.722768 0.723817 0.726979 0.729076 0.731668 0.735863 0.737871 0.739924 0.741048 0.744853 0.747311 0.748494 0.751761 0.755641 0.757319 0.760076 0.761949 0.764166 0.767148 0.76995 0.771523 0.77419 0.776183 0.777022 0.778071 0.779839 0.782835 0.786836 0.789503 0.791735 0.793383 0.794432 0.797114 0.798957 0.801474 0.803137 0.80495 0.806599 0.807827 0.808906 0.810689 0.811992 0.81373 0.816832 0.817911 0.81878 0.819394 0.820788 0.821432 0.822331 0.824848 0.82756 0.828818 0.830556 0.831515 0.83228 0.834632  ];
Yhuang = [0.000866448 0.0026591 0.00549746 0.0105169 0.0162235 0.0269495 0.0339259 0.0398566 0.045115 0.0542277 0.0637287 0.0708396 0.0778309 0.0855692 0.0958022 0.103257 0.111548 0.121975 0.13164 0.138572 0.148551 0.160995 0.172662 0.187915 0.19879 0.210607 0.222617 0.232566 0.243905 0.252704 0.264565 0.275575 0.288736 0.300911 0.31473 0.326546 0.338766 0.347266 0.357051 0.366209 0.375874 0.385345 0.396952 0.406349 0.412354 0.419644 0.427009 0.434822 0.442486 0.449582 0.456259 0.464371 0.47078 0.47692 0.481073 0.486914 0.493098 0.498626 0.504751 0.511876 0.517419 0.522543 0.527592 0.5317 0.536585 0.541754 0.545384 0.550194 0.553466 0.557081 0.560771 0.565178 0.56833 0.571646 0.575246 0.580296 0.584553 0.587451 0.589767 0.59395 0.596161 0.59873 0.602345 0.605244 0.608321 0.611144 0.612967 0.615327 0.619002 0.620989 0.624514 0.626501 0.628921 0.630744 0.634001 0.635823 0.638796 0.640977 0.642516 0.644308 0.645937 0.648416 0.650448 0.652659 0.655722 0.657111 0.658724 0.660651 0.662743 0.665252 0.66703 0.668898 0.670795 0.67196 0.673603 0.675187 0.677189 0.679146 0.680759 0.68291 0.684434 0.685689 0.687033 0.688303 0.69035 0.691888 0.693053 0.694607 0.697221 0.699522 0.701091 0.702495 0.703451 0.70493 0.706603 0.708635 0.709875 0.711189 0.713042 0.715073 0.716896 0.720152 0.721482 0.722856 0.724709 0.726098 0.727293 0.728264 0.730206 0.73167 0.733388 0.734494 0.735629 0.737078 0.737944 0.739498 0.740633 0.742068 0.743322 0.74522 0.746474 0.747804 0.749895 0.751315 0.754362 0.755557 0.756887 0.758007 0.759561 0.761144 0.762563 0.764207 0.765984 0.767583 0.770362 0.772005 0.77314 0.774395 0.775904 0.777203 0.778653 0.779952 0.781013 0.782671 0.784165 0.785405 0.786376 0.787631 0.788975 0.790484 0.792053 0.793382 0.794443 0.795862 0.79749 0.799134 0.799761 0.800433 0.801554 0.803092 ];
Yhuang_all = [5.9755e-05 0.00267404 0.00627428 0.0112489 0.0171198 0.0249776 0.0324768 0.0398566 0.0493576 0.0579474 0.0652076 0.0727069 0.0810726 0.0877054 0.0965491 0.10611 0.114162 0.121437 0.131162 0.140529 0.150642 0.161533 0.172662 0.183119 0.193352 0.201912 0.213564 0.225007 0.234628 0.246176 0.261339 0.270182 0.2781 0.286944 0.295802 0.307215 0.316687 0.324619 0.332417 0.342082 0.352555 0.361981 0.368449 0.375964 0.383403 0.392381 0.400792 0.408918 0.415641 0.424201 0.431297 0.436525 0.441321 0.446938 0.454631 0.458485 0.464416 0.470436 0.476785 0.483702 0.489244 0.494966 0.500239 0.507514 0.513505 0.517673 0.521168 0.526023 0.530669 0.534987 0.540125 0.543741 0.547744 0.551673 0.555438 0.557858 0.561772 0.564999 0.568673 0.571377 0.575232 0.579355 0.58415 0.587676 0.590245 0.592546 0.596071 0.599014 0.602017 0.605363 0.607843 0.611622 0.61579 0.6196 0.622572 0.624993 0.627428 0.630102 0.632342 0.635016 0.637347 0.639349 0.640917 0.644846 0.647117 0.650075 0.652823 0.654526 0.656857 0.658679 0.661488 0.664281 0.666687 0.668494 0.671168 0.673424 0.676203 0.677756 0.680236 0.682566 0.685285 0.687422 0.689528 0.691589 0.694308 0.695907 0.697625 0.69991 0.702091 0.704407 0.706035 0.708351 0.710188 0.712937 0.715013 0.716507 0.717822 0.719749 0.720989 0.722602 0.72432 0.72553 0.727054 0.728936 0.730415 0.731939 0.733881 0.73527 0.736824 0.738198 0.739633 0.741097 0.743068 0.744682 0.74631 0.748446 0.74997 0.751061 0.752659 0.754138 0.755303 0.756394 0.757828 0.759531 0.761099 0.762668 0.763953 0.765716 0.767195 0.768375 0.770122 0.772587 0.773812 0.774918 0.775874 0.777592 0.779683 0.780669 0.782357 0.783478 0.784299 0.7853 0.786495 0.787541 0.788871 0.789737 0.791306 0.792411 0.793248 0.794428 0.795757 0.796474 0.796952 0.797774 0.798745 0.799193 0.799731 0.800732 0.802271 0.803301 ];

fig = figure('Position', [0 0 825 450]);
plot(X, Yfinal*100, 'r', 'LineWidth', 3), hold all;
%plot(X, Ygtfinal*100, 'm', 'LineWidth', 3), hold all;
%plot(X, Yhuang*100, 'k', 'LineWidth', 3), hold all;
%plot(X, Yhuang_all*100, '-', 'color', [.5 .5 .5], 'LineWidth', 3), hold all;
%plot(X, Yfuzzy*100, 'b', 'LineWidth', 3), hold all;
plot(X, accury*100,color,'LineWidth', 3);
plot(X, accury1*100,color1,'LineWidth', 3);
%plot(X, Yinit*100, '--r', 'LineWidth', 2), hold all;
xlabel('Euclidean Distance');
ylabel('% Correspondences');
axis([0, 0.25, 0, 100]);
set(gca,'XTick',0:.05:.25);
set(gca,'YTick',0:10:100);
%legend('Our:all', 'Our:gtonly', 'Huang12:gtonly', 'Kim12:gtonly', 'Our:init', 'Location', 'SE');
%legend('Our:all', 'Our:gtonly', 'Huang12:gtonly', 'Huang12:1000', 'Kim12:gtonly', 'Our:init', 'Location', 'SE');
%legend('Our:all', 'Huang12:gtonly', 'Huang12:1000', 'Kim12:gtonly', 'Our:init', 'Location', 'SE');
%legend('Kim et al. 2013', 'Deformation(old)','Deformation(new)+gtlabel',4);
legend('Kim et al. 2013', 'old','new',4);
title('bike');
fName = 'chair_perpoint_new.pdf';
% cmnpfx = '/Users/vk/Research/TalksAndPapers/2013/TemplateAnalysis/';
% outFile1 = [ cmnpfx 'nosvn/data/CorrespondenceResults/' fName];
% outFile2 = [ cmnpfx 'evolving_template/figures/quantitative/' fName];
print(fig, '-dpdf', fName);
% %system(['/usr/texbin/pdfcrop ' outFile1 ' ' outFile2])
% ['pdfcrop ' outFile1 ' ' outFile2]
% %close(fig);
